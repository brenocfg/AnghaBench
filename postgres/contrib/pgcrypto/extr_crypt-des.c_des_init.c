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
typedef  long uint32 ;

/* Variables and functions */
 size_t* IP ; 
 long* _crypt_bits32 ; 
 int* _crypt_bits8 ; 
 long* bits24 ; 
 long* bits28 ; 
 long** comp_maskl ; 
 long** comp_maskr ; 
 int* comp_perm ; 
 int des_initialised ; 
 size_t* final_perm ; 
 long** fp_maskl ; 
 long** fp_maskr ; 
 int* init_perm ; 
 int* inv_comp_perm ; 
 int* inv_key_perm ; 
 long** ip_maskl ; 
 long** ip_maskr ; 
 int* key_perm ; 
 long** key_perm_maskl ; 
 long** key_perm_maskr ; 
 int** m_sbox ; 
 long old_rawkey0 ; 
 long old_rawkey1 ; 
 long old_salt ; 
 int* pbox ; 
 long** psbox ; 
 long saltbits ; 
 int** sbox ; 
 int* u_key_perm ; 
 int** u_sbox ; 
 size_t* un_pbox ; 

__attribute__((used)) static void
des_init(void)
{
	int			i,
				j,
				b,
				k,
				inbit,
				obit;
	uint32	   *p,
			   *il,
			   *ir,
			   *fl,
			   *fr;

	old_rawkey0 = old_rawkey1 = 0L;
	saltbits = 0L;
	old_salt = 0L;
	bits24 = (bits28 = _crypt_bits32 + 4) + 4;

	/*
	 * Invert the S-boxes, reordering the input bits.
	 */
	for (i = 0; i < 8; i++)
		for (j = 0; j < 64; j++)
		{
			b = (j & 0x20) | ((j & 1) << 4) | ((j >> 1) & 0xf);
			u_sbox[i][j] = sbox[i][b];
		}

	/*
	 * Convert the inverted S-boxes into 4 arrays of 8 bits. Each will handle
	 * 12 bits of the S-box input.
	 */
	for (b = 0; b < 4; b++)
		for (i = 0; i < 64; i++)
			for (j = 0; j < 64; j++)
				m_sbox[b][(i << 6) | j] =
					(u_sbox[(b << 1)][i] << 4) |
					u_sbox[(b << 1) + 1][j];

	/*
	 * Set up the initial & final permutations into a useful form, and
	 * initialise the inverted key permutation.
	 */
	for (i = 0; i < 64; i++)
	{
		init_perm[final_perm[i] = IP[i] - 1] = i;
		inv_key_perm[i] = 255;
	}

	/*
	 * Invert the key permutation and initialise the inverted key compression
	 * permutation.
	 */
	for (i = 0; i < 56; i++)
	{
		u_key_perm[i] = key_perm[i] - 1;
		inv_key_perm[key_perm[i] - 1] = i;
		inv_comp_perm[i] = 255;
	}

	/*
	 * Invert the key compression permutation.
	 */
	for (i = 0; i < 48; i++)
		inv_comp_perm[comp_perm[i] - 1] = i;

	/*
	 * Set up the OR-mask arrays for the initial and final permutations, and
	 * for the key initial and compression permutations.
	 */
	for (k = 0; k < 8; k++)
	{
		for (i = 0; i < 256; i++)
		{
			*(il = &ip_maskl[k][i]) = 0L;
			*(ir = &ip_maskr[k][i]) = 0L;
			*(fl = &fp_maskl[k][i]) = 0L;
			*(fr = &fp_maskr[k][i]) = 0L;
			for (j = 0; j < 8; j++)
			{
				inbit = 8 * k + j;
				if (i & _crypt_bits8[j])
				{
					if ((obit = init_perm[inbit]) < 32)
						*il |= _crypt_bits32[obit];
					else
						*ir |= _crypt_bits32[obit - 32];
					if ((obit = final_perm[inbit]) < 32)
						*fl |= _crypt_bits32[obit];
					else
						*fr |= _crypt_bits32[obit - 32];
				}
			}
		}
		for (i = 0; i < 128; i++)
		{
			*(il = &key_perm_maskl[k][i]) = 0L;
			*(ir = &key_perm_maskr[k][i]) = 0L;
			for (j = 0; j < 7; j++)
			{
				inbit = 8 * k + j;
				if (i & _crypt_bits8[j + 1])
				{
					if ((obit = inv_key_perm[inbit]) == 255)
						continue;
					if (obit < 28)
						*il |= bits28[obit];
					else
						*ir |= bits28[obit - 28];
				}
			}
			*(il = &comp_maskl[k][i]) = 0L;
			*(ir = &comp_maskr[k][i]) = 0L;
			for (j = 0; j < 7; j++)
			{
				inbit = 7 * k + j;
				if (i & _crypt_bits8[j + 1])
				{
					if ((obit = inv_comp_perm[inbit]) == 255)
						continue;
					if (obit < 24)
						*il |= bits24[obit];
					else
						*ir |= bits24[obit - 24];
				}
			}
		}
	}

	/*
	 * Invert the P-box permutation, and convert into OR-masks for handling
	 * the output of the S-box arrays setup above.
	 */
	for (i = 0; i < 32; i++)
		un_pbox[pbox[i] - 1] = i;

	for (b = 0; b < 4; b++)
		for (i = 0; i < 256; i++)
		{
			*(p = &psbox[b][i]) = 0L;
			for (j = 0; j < 8; j++)
			{
				if (i & _crypt_bits8[j])
					*p |= _crypt_bits32[un_pbox[8 * b + j]];
			}
		}

	des_initialised = 1;
}