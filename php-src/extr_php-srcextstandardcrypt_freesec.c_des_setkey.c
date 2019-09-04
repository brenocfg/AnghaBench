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
typedef  int uint32_t ;
typedef  scalar_t__ u_char ;
struct php_crypt_extended_data {int old_rawkey0; int old_rawkey1; int* de_keysl; int* en_keysl; int* de_keysr; int* en_keysr; } ;

/* Variables and functions */
 int** comp_maskl ; 
 int** comp_maskr ; 
 int** key_perm_maskl ; 
 int** key_perm_maskr ; 
 scalar_t__* key_shifts ; 

__attribute__((used)) static int
des_setkey(const char *key, struct php_crypt_extended_data *data)
{
	uint32_t	k0, k1, rawkey0, rawkey1;
	int	shifts, round;

	rawkey0 =
		(uint32_t)(u_char)key[3] |
		((uint32_t)(u_char)key[2] << 8) |
		((uint32_t)(u_char)key[1] << 16) |
		((uint32_t)(u_char)key[0] << 24);
	rawkey1 =
		(uint32_t)(u_char)key[7] |
		((uint32_t)(u_char)key[6] << 8) |
		((uint32_t)(u_char)key[5] << 16) |
		((uint32_t)(u_char)key[4] << 24);

	if ((rawkey0 | rawkey1)
	    && rawkey0 == data->old_rawkey0
	    && rawkey1 == data->old_rawkey1) {
		/*
		 * Already setup for this key.
		 * This optimisation fails on a zero key (which is weak and
		 * has bad parity anyway) in order to simplify the starting
		 * conditions.
		 */
		return(0);
	}
	data->old_rawkey0 = rawkey0;
	data->old_rawkey1 = rawkey1;

	/*
	 *	Do key permutation and split into two 28-bit subkeys.
	 */
	k0 = key_perm_maskl[0][rawkey0 >> 25]
	   | key_perm_maskl[1][(rawkey0 >> 17) & 0x7f]
	   | key_perm_maskl[2][(rawkey0 >> 9) & 0x7f]
	   | key_perm_maskl[3][(rawkey0 >> 1) & 0x7f]
	   | key_perm_maskl[4][rawkey1 >> 25]
	   | key_perm_maskl[5][(rawkey1 >> 17) & 0x7f]
	   | key_perm_maskl[6][(rawkey1 >> 9) & 0x7f]
	   | key_perm_maskl[7][(rawkey1 >> 1) & 0x7f];
	k1 = key_perm_maskr[0][rawkey0 >> 25]
	   | key_perm_maskr[1][(rawkey0 >> 17) & 0x7f]
	   | key_perm_maskr[2][(rawkey0 >> 9) & 0x7f]
	   | key_perm_maskr[3][(rawkey0 >> 1) & 0x7f]
	   | key_perm_maskr[4][rawkey1 >> 25]
	   | key_perm_maskr[5][(rawkey1 >> 17) & 0x7f]
	   | key_perm_maskr[6][(rawkey1 >> 9) & 0x7f]
	   | key_perm_maskr[7][(rawkey1 >> 1) & 0x7f];
	/*
	 *	Rotate subkeys and do compression permutation.
	 */
	shifts = 0;
	for (round = 0; round < 16; round++) {
		uint32_t	t0, t1;

		shifts += key_shifts[round];

		t0 = (k0 << shifts) | (k0 >> (28 - shifts));
		t1 = (k1 << shifts) | (k1 >> (28 - shifts));

		data->de_keysl[15 - round] =
		data->en_keysl[round] = comp_maskl[0][(t0 >> 21) & 0x7f]
				| comp_maskl[1][(t0 >> 14) & 0x7f]
				| comp_maskl[2][(t0 >> 7) & 0x7f]
				| comp_maskl[3][t0 & 0x7f]
				| comp_maskl[4][(t1 >> 21) & 0x7f]
				| comp_maskl[5][(t1 >> 14) & 0x7f]
				| comp_maskl[6][(t1 >> 7) & 0x7f]
				| comp_maskl[7][t1 & 0x7f];

		data->de_keysr[15 - round] =
		data->en_keysr[round] = comp_maskr[0][(t0 >> 21) & 0x7f]
				| comp_maskr[1][(t0 >> 14) & 0x7f]
				| comp_maskr[2][(t0 >> 7) & 0x7f]
				| comp_maskr[3][t0 & 0x7f]
				| comp_maskr[4][(t1 >> 21) & 0x7f]
				| comp_maskr[5][(t1 >> 14) & 0x7f]
				| comp_maskr[6][(t1 >> 7) & 0x7f]
				| comp_maskr[7][t1 & 0x7f];
	}
	return(0);
}