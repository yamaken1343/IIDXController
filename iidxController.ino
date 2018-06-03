#include <Arduino.h>
#include "HID-Project.h"

#define THRESHOLD 980

#define KEY_1 8
#define KEY_2 7
#define KEY_3 6
#define KEY_4 5
#define KEY_5 4
#define KEY_6 3
#define KEY_7 2
#define START 9
#define SELECT 10
#define PHOTO_A A0
#define PHOTO_B A1

#define KEY_CODE_1 'z'
#define KEY_CODE_2 's'
#define KEY_CODE_3 'x'
#define KEY_CODE_4 'd'
#define KEY_CODE_5 'c'
#define KEY_CODE_6 'f'
#define KEY_CODE_7 'v'
#define KEY_CODE_SCR1 KEY_LEFT_SHIFT
#define KEY_CODE_SCR2 KEY_LEFT_CTRL
#define KEY_CODE_START 'q'
#define KEY_CODE_SELECT 'w'


uint8_t photoA, photoB;
uint8_t before = 0;
static const int encoder[]={ 0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};
int scratch,i,r; 

int scratch_read(){
  photoA = analogRead(PHOTO_A)>THRESHOLD ? 1:0;
  photoB = analogRead(PHOTO_B)>THRESHOLD ? 1:0;
  uint8_t ab = (photoA<<1) | photoB;
  uint8_t abcd = (ab << 2) | before;
  int encodeNum = encoder[abcd&0x0f];
  before = ab;
  return encodeNum;
}

void setup() {
  pinMode(KEY_1, INPUT_PULLUP);
  pinMode(KEY_2, INPUT_PULLUP);
  pinMode(KEY_3, INPUT_PULLUP);
  pinMode(KEY_4, INPUT_PULLUP);
  pinMode(KEY_5, INPUT_PULLUP);
  pinMode(KEY_6, INPUT_PULLUP);
  pinMode(KEY_7, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(PHOTO_A, INPUT);
  pinMode(PHOTO_B, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(KEY_1) == LOW) Serial.println(KEY_CODE_1);
  if(digitalRead(KEY_2) == LOW) Serial.println(KEY_CODE_2);
  if(digitalRead(KEY_3) == LOW) Serial.println(KEY_CODE_3);
  if(digitalRead(KEY_4) == LOW) Serial.println(KEY_CODE_4);
  if(digitalRead(KEY_5) == LOW) Serial.println(KEY_CODE_5);
  if(digitalRead(KEY_6) == LOW) Serial.println(KEY_CODE_6);
  if(digitalRead(KEY_7) == LOW) Serial.println(KEY_CODE_7);
  if(digitalRead(START) == LOW) Serial.println(KEY_CODE_START);
  if(digitalRead(SELECT) == LOW) Serial.println(KEY_CODE_SELECT);
  scratch = scratch_read();
  if(scratch == 1) Serial.println("up");
  else if(scratch == -1) Serial.println("down");
  
}
