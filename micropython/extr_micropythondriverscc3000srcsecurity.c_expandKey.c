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
typedef  size_t UINT8 ;
typedef  int UINT16 ;

/* Variables and functions */
 size_t* Rcon ; 
 size_t* sbox ; 

void expandKey(UINT8 *expandedKey, UINT8 *key)
{
  UINT16 ii, buf1;
  for (ii=0;ii<16;ii++)
    expandedKey[ii] = key[ii];
  for (ii=1;ii<11;ii++){
    buf1 = expandedKey[ii*16 - 4];
    expandedKey[ii*16 + 0] = sbox[expandedKey[ii*16 - 3]]^expandedKey[(ii-1)*16 + 0]^Rcon[ii];
    expandedKey[ii*16 + 1] = sbox[expandedKey[ii*16 - 2]]^expandedKey[(ii-1)*16 + 1];
    expandedKey[ii*16 + 2] = sbox[expandedKey[ii*16 - 1]]^expandedKey[(ii-1)*16 + 2];
    expandedKey[ii*16 + 3] = sbox[buf1                  ]^expandedKey[(ii-1)*16 + 3];
    expandedKey[ii*16 + 4] = expandedKey[(ii-1)*16 + 4]^expandedKey[ii*16 + 0];
    expandedKey[ii*16 + 5] = expandedKey[(ii-1)*16 + 5]^expandedKey[ii*16 + 1];
    expandedKey[ii*16 + 6] = expandedKey[(ii-1)*16 + 6]^expandedKey[ii*16 + 2];
    expandedKey[ii*16 + 7] = expandedKey[(ii-1)*16 + 7]^expandedKey[ii*16 + 3];
    expandedKey[ii*16 + 8] = expandedKey[(ii-1)*16 + 8]^expandedKey[ii*16 + 4];
    expandedKey[ii*16 + 9] = expandedKey[(ii-1)*16 + 9]^expandedKey[ii*16 + 5];
    expandedKey[ii*16 +10] = expandedKey[(ii-1)*16 +10]^expandedKey[ii*16 + 6];
    expandedKey[ii*16 +11] = expandedKey[(ii-1)*16 +11]^expandedKey[ii*16 + 7];
    expandedKey[ii*16 +12] = expandedKey[(ii-1)*16 +12]^expandedKey[ii*16 + 8];
    expandedKey[ii*16 +13] = expandedKey[(ii-1)*16 +13]^expandedKey[ii*16 + 9];
    expandedKey[ii*16 +14] = expandedKey[(ii-1)*16 +14]^expandedKey[ii*16 +10];
    expandedKey[ii*16 +15] = expandedKey[(ii-1)*16 +15]^expandedKey[ii*16 +11];
  }
	
}