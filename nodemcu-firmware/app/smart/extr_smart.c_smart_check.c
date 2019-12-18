#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int NIBBLE_PER_BYTE ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int smart_check(uint8_t *nibble, uint16_t len, uint8_t *dst, uint8_t *got){
  if(len == 0)
    return 0;
  uint16_t dst_len = len/NIBBLE_PER_BYTE;
  uint16_t byte_num = 0, bit_num = 0;
  int i = 0, res = 1; // assume ok.
  memset(dst,0,dst_len);

  if(NIBBLE_PER_BYTE==1){
    for(i=0;i<len;i++){
      byte_num = (i) / 8;
      bit_num = (i) % 8;
      if(0x20>nibble[i] || nibble[i]>=0x7F){ // not printable
        NODE_DBG("Smart: got np byte %d:%02x\n", i, nibble[i]);
        nibble[i] = 0;
        got[byte_num] &= ~(0x1 << bit_num);  // clear the bit
        res = 0;  // not ok
      } else {
        dst[i] = nibble[i];
      }
    }
    return res;
  }

  // NIBBLE_PER_BYTE == 2
  if((len%NIBBLE_PER_BYTE) != 0){
    // this should not happen
    NODE_DBG("Smart: smart_check got odd len\n");
    return 0;
  }

  if(len == 2){
    // only one byte
    if(nibble[0]<=0xF && ((nibble[0]^0x1)&0xF == (nibble[1]>>4)) ){
      dst[0] = ((nibble[0]&0xF)<<4) + (nibble[1]&0xF);
      res = 1;
    }else{
      nibble[0] = 0;
      nibble[1] = 0;
      got[0] &= ~(0x3 << 0);  // clear the 0 bit
      res = 0;  // not ok
    }
    return res;
  }

  res = 1;  // assume ok.
  for(i=len-2;i>0;i--){
    bool forward = ( ((nibble[i]&0xF)^((i+1)&0xF)) == (nibble[i+1]>>4) );
    bool back = ( ((nibble[i-1]&0xF)^(i&0xF)) == (nibble[i]>>4) );
    if(!forward || !back){
    // wrong forward, or wrong back, replace i-1, i and i+1, until get right back, forward
      NODE_DBG("check: wf %d:%02x %02x %02x\n",i,nibble[i-1],nibble[i], nibble[i+1]);
      byte_num = (i-1) / 8;
      bit_num = (i-1) % 8;
      nibble[i-1] = 0;
      got[byte_num] &= ~(0x1 << bit_num);  // clear the bit

      byte_num = (i) / 8;
      bit_num = (i) % 8;
      nibble[i] = 0;
      got[byte_num] &= ~(0x1 << bit_num);  // clear the bit

      byte_num = (i+1) / 8;
      bit_num = (i+1) % 8;
      nibble[i+1] = 0;
      got[byte_num] &= ~(0x1 << bit_num);  // clear the bit
      res = 0;
      return res; // once there is error,
    }

    if((i%NIBBLE_PER_BYTE) == 0) { // i == even
      dst[i/NIBBLE_PER_BYTE] = ((nibble[i]&0xF)<<4) + (nibble[i+1]&0xF);
    }
  }

  if(i==0){
    dst[0] = ((nibble[0]&0xF)<<4) + (nibble[1]&0xF);
  }

  for(i=0;i<dst_len;i++){   // check for non-printable byte
    // NODE_DBG("nibble %d:%02x %02x->%02x\n", i, nibble[i*NIBBLE_PER_BYTE], nibble[i*NIBBLE_PER_BYTE+1], dst[i]);
    byte_num = (i*NIBBLE_PER_BYTE) / 8;
    bit_num = (i*NIBBLE_PER_BYTE) % 8;
    if(0x20>dst[i] || dst[i]>=0x7F){ // not printable
      NODE_DBG("Smart: got np byte %d:%02x\n", i, dst[i]);
      dst[i] = 0; // reset byte
      nibble[i*NIBBLE_PER_BYTE] = 0;  // reset hi-nibble
      nibble[i*NIBBLE_PER_BYTE+1] = 0;  // reset lo-nibble
      got[byte_num] &= ~(0x3 << bit_num);  // clear the bit
      res = 0;  // not ok
    }
  }
  return res;
}