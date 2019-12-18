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
typedef  size_t ut8 ;
typedef  int ut32 ;
struct aes_state {int rounds; } ;

/* Variables and functions */
 int* FT0 ; 
 int* FT1 ; 
 int* FT2 ; 
 int* FT3 ; 
 int Nb ; 
 int /*<<< orphan*/  Nr_AES256 ; 
 size_t* Sbox ; 
 int /*<<< orphan*/  aes_expkey (struct aes_state*,int***) ; 

void aes_encrypt (struct aes_state *st, ut8 *in, ut8 *result) {
#ifdef _MSC_VER
	ut32 expkey[2][Nr_AES256 + 1][Nb];
#else
	ut32 expkey[2][st->rounds + 1][Nb];
#endif
	aes_expkey(st, expkey);

	ut32 t0, t1, t2, t3, tt;
	ut32 a0, a1, a2, a3, r;

	t0 = *in++ << 24;
	t0 |= *in++ << 16;
	t0 |= *in++ << 8;
	t0 |= *in++;
	t0 ^= expkey[0][0][0];

	t1 = *in++ << 24;
	t1 |= *in++ << 16;
	t1 |= *in++ << 8;
	t1 |= *in++;
	t1 ^= expkey[0][0][1];

	t2 = *in++ << 24;
	t2 |= *in++ << 16;
	t2 |= *in++ << 8;
	t2 |= *in++;
	t2 ^= expkey[0][0][2];

	t3 = *in++ << 24;
	t3 |= *in++ << 16;
	t3 |= *in++ << 8;
	t3 |= *in++;
	t3 ^= expkey[0][0][3];

	// Apply Round Transforms
	for (r = 1; r < st->rounds; r++) {
		a0 = (FT0[(ut8)(t0 >> 24)] ^ FT1[(ut8)(t1 >> 16)] ^ FT2[(ut8)(t2 >> 8)] ^
				FT3[(ut8)t3]);
		a1 = (FT0[(ut8)(t1 >> 24)] ^ FT1[(ut8)(t2 >> 16)] ^ FT2[(ut8)(t3 >> 8)] ^
				FT3[(ut8)t0]);
		a2 = (FT0[(ut8)(t2 >> 24)] ^ FT1[(ut8)(t3 >> 16)] ^ FT2[(ut8)(t0 >> 8)] ^
				FT3[(ut8)t1]);
		a3 = (FT0[(ut8)(t3 >> 24)] ^ FT1[(ut8)(t0 >> 16)] ^ FT2[(ut8)(t1 >> 8)] ^
				FT3[(ut8)t2]);
		t0 = a0 ^ expkey[0][r][0];
		t1 = a1 ^ expkey[0][r][1];
		t2 = a2 ^ expkey[0][r][2];
		t3 = a3 ^ expkey[0][r][3];
	}

	// Last Round is special

	tt = expkey[0][st->rounds][0];
	result[0] = Sbox[(ut8)(t0 >> 24)] ^ (ut8)(tt >> 24);
	result[1] = Sbox[(ut8)(t1 >> 16)] ^ (ut8)(tt >> 16);
	result[2] = Sbox[(ut8)(t2 >> 8)] ^ (ut8)(tt >> 8);
	result[3] = Sbox[(ut8)t3] ^ (ut8)tt;

	tt = expkey[0][st->rounds][1];
	result[4] = Sbox[(ut8)(t1 >> 24)] ^ (ut8)(tt >> 24);
	result[5] = Sbox[(ut8)(t2 >> 16)] ^ (ut8)(tt >> 16);
	result[6] = Sbox[(ut8)(t3 >> 8)] ^ (ut8)(tt >> 8);
	result[7] = Sbox[(ut8)t0] ^ (ut8)tt;

	tt = expkey[0][st->rounds][2];
	result[8] = Sbox[(ut8)(t2 >> 24)] ^ (ut8)(tt >> 24);
	result[9] = Sbox[(ut8)(t3 >> 16)] ^ (ut8)(tt >> 16);
	result[10] = Sbox[(ut8)(t0 >> 8)] ^ (ut8)(tt >> 8);
	result[11] = Sbox[(ut8)t1] ^ (ut8)tt;

	tt = expkey[0][st->rounds][3];
	result[12] = Sbox[(ut8)(t3 >> 24)] ^ (ut8)(tt >> 24);
	result[13] = Sbox[(ut8)(t0 >> 16)] ^ (ut8)(tt >> 16);
	result[14] = Sbox[(ut8)(t1 >> 8)] ^ (ut8)(tt >> 8);
	result[15] = Sbox[(ut8)t2] ^ (ut8)tt;
}