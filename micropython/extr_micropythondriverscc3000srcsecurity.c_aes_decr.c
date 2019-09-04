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
typedef  int INT8 ;

/* Variables and functions */
 size_t galois_mul2 (size_t) ; 
 size_t* rsbox ; 

void aes_decr(UINT8 *state, UINT8 *expandedKey)
{
  UINT8 buf1, buf2, buf3;
  INT8 round;
  round = 9;
	
  // initial addroundkey
  state[ 0]^=expandedKey[160];
  state[ 1]^=expandedKey[161];
  state[ 2]^=expandedKey[162];
  state[ 3]^=expandedKey[163];
  state[ 4]^=expandedKey[164];
  state[ 5]^=expandedKey[165];
  state[ 6]^=expandedKey[166];
  state[ 7]^=expandedKey[167];
  state[ 8]^=expandedKey[168];
  state[ 9]^=expandedKey[169];
  state[10]^=expandedKey[170];
  state[11]^=expandedKey[171];
  state[12]^=expandedKey[172];
  state[13]^=expandedKey[173];
  state[14]^=expandedKey[174]; 
  state[15]^=expandedKey[175];
	
  // 10th round without mixcols
  state[ 0]  = rsbox[state[ 0]] ^ expandedKey[(round*16)     ];
  state[ 4]  = rsbox[state[ 4]] ^ expandedKey[(round*16) +  4];
  state[ 8]  = rsbox[state[ 8]] ^ expandedKey[(round*16) +  8];
  state[12]  = rsbox[state[12]] ^ expandedKey[(round*16) + 12];
  // row 1
  buf1 =       rsbox[state[13]] ^ expandedKey[(round*16) +  1];
  state[13]  = rsbox[state[ 9]] ^ expandedKey[(round*16) + 13];
  state[ 9]  = rsbox[state[ 5]] ^ expandedKey[(round*16) +  9];
  state[ 5]  = rsbox[state[ 1]] ^ expandedKey[(round*16) +  5];
  state[ 1]  = buf1;
  // row 2
  buf1 =       rsbox[state[ 2]] ^ expandedKey[(round*16) + 10];
  buf2 =       rsbox[state[ 6]] ^ expandedKey[(round*16) + 14];
  state[ 2]  = rsbox[state[10]] ^ expandedKey[(round*16) +  2];
  state[ 6]  = rsbox[state[14]] ^ expandedKey[(round*16) +  6];
  state[10]  = buf1;
  state[14]  = buf2;
  // row 3
  buf1 =       rsbox[state[ 3]] ^ expandedKey[(round*16) + 15];
  state[ 3]  = rsbox[state[ 7]] ^ expandedKey[(round*16) +  3];
  state[ 7]  = rsbox[state[11]] ^ expandedKey[(round*16) +  7];
  state[11]  = rsbox[state[15]] ^ expandedKey[(round*16) + 11];
  state[15]  = buf1;
	
  for (round = 8; round >= 0; round--){
    // barreto
    //col1
    buf1 = galois_mul2(galois_mul2(state[0]^state[2]));
    buf2 = galois_mul2(galois_mul2(state[1]^state[3]));
    state[0] ^= buf1;     state[1] ^= buf2;    state[2] ^= buf1;    state[3] ^= buf2;
    //col2
    buf1 = galois_mul2(galois_mul2(state[4]^state[6]));
    buf2 = galois_mul2(galois_mul2(state[5]^state[7]));
    state[4] ^= buf1;    state[5] ^= buf2;    state[6] ^= buf1;    state[7] ^= buf2;
    //col3
    buf1 = galois_mul2(galois_mul2(state[8]^state[10]));
    buf2 = galois_mul2(galois_mul2(state[9]^state[11]));
    state[8] ^= buf1;    state[9] ^= buf2;    state[10] ^= buf1;    state[11] ^= buf2;
    //col4
    buf1 = galois_mul2(galois_mul2(state[12]^state[14]));
    buf2 = galois_mul2(galois_mul2(state[13]^state[15]));
    state[12] ^= buf1;    state[13] ^= buf2;    state[14] ^= buf1;    state[15] ^= buf2;
    // mixcolums //////////
    // col1
    buf1 = state[0] ^ state[1] ^ state[2] ^ state[3];
    buf2 = state[0];
    buf3 = state[0]^state[1]; buf3=galois_mul2(buf3); state[0] = state[0] ^ buf3 ^ buf1;
    buf3 = state[1]^state[2]; buf3=galois_mul2(buf3); state[1] = state[1] ^ buf3 ^ buf1;
    buf3 = state[2]^state[3]; buf3=galois_mul2(buf3); state[2] = state[2] ^ buf3 ^ buf1;
    buf3 = state[3]^buf2;     buf3=galois_mul2(buf3); state[3] = state[3] ^ buf3 ^ buf1;
    // col2
    buf1 = state[4] ^ state[5] ^ state[6] ^ state[7];
    buf2 = state[4];
    buf3 = state[4]^state[5]; buf3=galois_mul2(buf3); state[4] = state[4] ^ buf3 ^ buf1;
    buf3 = state[5]^state[6]; buf3=galois_mul2(buf3); state[5] = state[5] ^ buf3 ^ buf1;
    buf3 = state[6]^state[7]; buf3=galois_mul2(buf3); state[6] = state[6] ^ buf3 ^ buf1;
    buf3 = state[7]^buf2;     buf3=galois_mul2(buf3); state[7] = state[7] ^ buf3 ^ buf1;
    // col3
    buf1 = state[8] ^ state[9] ^ state[10] ^ state[11];
    buf2 = state[8];
    buf3 = state[8]^state[9];   buf3=galois_mul2(buf3); state[8] = state[8] ^ buf3 ^ buf1;
    buf3 = state[9]^state[10];  buf3=galois_mul2(buf3); state[9] = state[9] ^ buf3 ^ buf1;
    buf3 = state[10]^state[11]; buf3=galois_mul2(buf3); state[10] = state[10] ^ buf3 ^ buf1;
    buf3 = state[11]^buf2;      buf3=galois_mul2(buf3); state[11] = state[11] ^ buf3 ^ buf1;
    // col4
    buf1 = state[12] ^ state[13] ^ state[14] ^ state[15];
    buf2 = state[12];
    buf3 = state[12]^state[13]; buf3=galois_mul2(buf3); state[12] = state[12] ^ buf3 ^ buf1;
    buf3 = state[13]^state[14]; buf3=galois_mul2(buf3); state[13] = state[13] ^ buf3 ^ buf1;
    buf3 = state[14]^state[15]; buf3=galois_mul2(buf3); state[14] = state[14] ^ buf3 ^ buf1;
    buf3 = state[15]^buf2;      buf3=galois_mul2(buf3); state[15] = state[15] ^ buf3 ^ buf1;    
		
    // addroundkey, rsbox and shiftrows
    // row 0
    state[ 0]  = rsbox[state[ 0]] ^ expandedKey[(round*16)     ];
    state[ 4]  = rsbox[state[ 4]] ^ expandedKey[(round*16) +  4];
    state[ 8]  = rsbox[state[ 8]] ^ expandedKey[(round*16) +  8];
    state[12]  = rsbox[state[12]] ^ expandedKey[(round*16) + 12];
    // row 1
    buf1 =       rsbox[state[13]] ^ expandedKey[(round*16) +  1];
    state[13]  = rsbox[state[ 9]] ^ expandedKey[(round*16) + 13];
    state[ 9]  = rsbox[state[ 5]] ^ expandedKey[(round*16) +  9];
    state[ 5]  = rsbox[state[ 1]] ^ expandedKey[(round*16) +  5];
    state[ 1]  = buf1;
    // row 2
    buf1 =       rsbox[state[ 2]] ^ expandedKey[(round*16) + 10];
    buf2 =       rsbox[state[ 6]] ^ expandedKey[(round*16) + 14];
    state[ 2]  = rsbox[state[10]] ^ expandedKey[(round*16) +  2];
    state[ 6]  = rsbox[state[14]] ^ expandedKey[(round*16) +  6];
    state[10]  = buf1;
    state[14]  = buf2;
    // row 3
    buf1 =       rsbox[state[ 3]] ^ expandedKey[(round*16) + 15];
    state[ 3]  = rsbox[state[ 7]] ^ expandedKey[(round*16) +  3];
    state[ 7]  = rsbox[state[11]] ^ expandedKey[(round*16) +  7];
    state[11]  = rsbox[state[15]] ^ expandedKey[(round*16) + 11];
    state[15]  = buf1;
  }
	
}