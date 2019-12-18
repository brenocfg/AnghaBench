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
struct php_crypt_extended_data {int* en_keysl; int* en_keysr; int* de_keysl; int* de_keysr; int saltbits; } ;

/* Variables and functions */
 int** fp_maskl ; 
 int** fp_maskr ; 
 int** ip_maskl ; 
 int** ip_maskr ; 
 size_t** m_sbox ; 
 int** psbox ; 

__attribute__((used)) static int
do_des(uint32_t l_in, uint32_t r_in, uint32_t *l_out, uint32_t *r_out,
	int count, struct php_crypt_extended_data *data)
{
	/*
	 *	l_in, r_in, l_out, and r_out are in pseudo-"big-endian" format.
	 */
	uint32_t	l, r, *kl, *kr, *kl1, *kr1;
	uint32_t	f, r48l, r48r, saltbits;
	int	round;

	if (count == 0) {
		return(1);
	} else if (count > 0) {
		/*
		 * Encrypting
		 */
		kl1 = data->en_keysl;
		kr1 = data->en_keysr;
	} else {
		/*
		 * Decrypting
		 */
		count = -count;
		kl1 = data->de_keysl;
		kr1 = data->de_keysr;
	}

	/*
	 *	Do initial permutation (IP).
	 */
	l = ip_maskl[0][l_in >> 24]
	  | ip_maskl[1][(l_in >> 16) & 0xff]
	  | ip_maskl[2][(l_in >> 8) & 0xff]
	  | ip_maskl[3][l_in & 0xff]
	  | ip_maskl[4][r_in >> 24]
	  | ip_maskl[5][(r_in >> 16) & 0xff]
	  | ip_maskl[6][(r_in >> 8) & 0xff]
	  | ip_maskl[7][r_in & 0xff];
	r = ip_maskr[0][l_in >> 24]
	  | ip_maskr[1][(l_in >> 16) & 0xff]
	  | ip_maskr[2][(l_in >> 8) & 0xff]
	  | ip_maskr[3][l_in & 0xff]
	  | ip_maskr[4][r_in >> 24]
	  | ip_maskr[5][(r_in >> 16) & 0xff]
	  | ip_maskr[6][(r_in >> 8) & 0xff]
	  | ip_maskr[7][r_in & 0xff];

	saltbits = data->saltbits;
	while (count--) {
		/*
		 * Do each round.
		 */
		kl = kl1;
		kr = kr1;
		round = 16;
		while (round--) {
			/*
			 * Expand R to 48 bits (simulate the E-box).
			 */
			r48l	= ((r & 0x00000001) << 23)
				| ((r & 0xf8000000) >> 9)
				| ((r & 0x1f800000) >> 11)
				| ((r & 0x01f80000) >> 13)
				| ((r & 0x001f8000) >> 15);

			r48r	= ((r & 0x0001f800) << 7)
				| ((r & 0x00001f80) << 5)
				| ((r & 0x000001f8) << 3)
				| ((r & 0x0000001f) << 1)
				| ((r & 0x80000000) >> 31);
			/*
			 * Do salting for crypt() and friends, and
			 * XOR with the permuted key.
			 */
			f = (r48l ^ r48r) & saltbits;
			r48l ^= f ^ *kl++;
			r48r ^= f ^ *kr++;
			/*
			 * Do sbox lookups (which shrink it back to 32 bits)
			 * and do the pbox permutation at the same time.
			 */
			f = psbox[0][m_sbox[0][r48l >> 12]]
			  | psbox[1][m_sbox[1][r48l & 0xfff]]
			  | psbox[2][m_sbox[2][r48r >> 12]]
			  | psbox[3][m_sbox[3][r48r & 0xfff]];
			/*
			 * Now that we've permuted things, complete f().
			 */
			f ^= l;
			l = r;
			r = f;
		}
		r = l;
		l = f;
	}
	/*
	 * Do final permutation (inverse of IP).
	 */
	*l_out	= fp_maskl[0][l >> 24]
		| fp_maskl[1][(l >> 16) & 0xff]
		| fp_maskl[2][(l >> 8) & 0xff]
		| fp_maskl[3][l & 0xff]
		| fp_maskl[4][r >> 24]
		| fp_maskl[5][(r >> 16) & 0xff]
		| fp_maskl[6][(r >> 8) & 0xff]
		| fp_maskl[7][r & 0xff];
	*r_out	= fp_maskr[0][l >> 24]
		| fp_maskr[1][(l >> 16) & 0xff]
		| fp_maskr[2][(l >> 8) & 0xff]
		| fp_maskr[3][l & 0xff]
		| fp_maskr[4][r >> 24]
		| fp_maskr[5][(r >> 16) & 0xff]
		| fp_maskr[6][(r >> 8) & 0xff]
		| fp_maskr[7][r & 0xff];
	return(0);
}