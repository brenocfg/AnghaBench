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
typedef  int u4byte ;
typedef  size_t u1byte ;

/* Variables and functions */
 scalar_t__ ff_mult (int,size_t) ; 
 int** fl_tab ; 
 int** ft_tab ; 
 int** il_tab ; 
 size_t* isb_tab ; 
 int** it_tab ; 
 int* log_tab ; 
 size_t* pow_tab ; 
 size_t* rco_tab ; 
 void* rotl (int,int) ; 
 size_t* sbx_tab ; 
 int tab_gen ; 

__attribute__((used)) static void
gen_tabs(void)
{
#ifndef PRE_CALC_TABLES
	u4byte		i,
				t;
	u1byte		p,
				q;

	/* log and power tables for GF(2**8) finite field with	*/
	/* 0x11b as modular polynomial - the simplest primitive	*/
	/* root is 0x11, used here to generate the tables		*/

	for (i = 0, p = 1; i < 256; ++i)
	{
		pow_tab[i] = (u1byte) p;
		log_tab[p] = (u1byte) i;

		p = p ^ (p << 1) ^ (p & 0x80 ? 0x01b : 0);
	}

	log_tab[1] = 0;
	p = 1;

	for (i = 0; i < 10; ++i)
	{
		rco_tab[i] = p;

		p = (p << 1) ^ (p & 0x80 ? 0x1b : 0);
	}

	/* note that the affine byte transformation matrix in	*/
	/* rijndael specification is in big endian format with	*/
	/* bit 0 as the most significant bit. In the remainder	*/
	/* of the specification the bits are numbered from the	*/
	/* least significant end of a byte.                     */

	for (i = 0; i < 256; ++i)
	{
		p = (i ? pow_tab[255 - log_tab[i]] : 0);
		q = p;
		q = (q >> 7) | (q << 1);
		p ^= q;
		q = (q >> 7) | (q << 1);
		p ^= q;
		q = (q >> 7) | (q << 1);
		p ^= q;
		q = (q >> 7) | (q << 1);
		p ^= q ^ 0x63;
		sbx_tab[i] = (u1byte) p;
		isb_tab[p] = (u1byte) i;
	}

	for (i = 0; i < 256; ++i)
	{
		p = sbx_tab[i];

#ifdef	LARGE_TABLES

		t = p;
		fl_tab[0][i] = t;
		fl_tab[1][i] = rotl(t, 8);
		fl_tab[2][i] = rotl(t, 16);
		fl_tab[3][i] = rotl(t, 24);
#endif
		t = ((u4byte) ff_mult(2, p)) |
			((u4byte) p << 8) |
			((u4byte) p << 16) |
			((u4byte) ff_mult(3, p) << 24);

		ft_tab[0][i] = t;
		ft_tab[1][i] = rotl(t, 8);
		ft_tab[2][i] = rotl(t, 16);
		ft_tab[3][i] = rotl(t, 24);

		p = isb_tab[i];

#ifdef	LARGE_TABLES

		t = p;
		il_tab[0][i] = t;
		il_tab[1][i] = rotl(t, 8);
		il_tab[2][i] = rotl(t, 16);
		il_tab[3][i] = rotl(t, 24);
#endif
		t = ((u4byte) ff_mult(14, p)) |
			((u4byte) ff_mult(9, p) << 8) |
			((u4byte) ff_mult(13, p) << 16) |
			((u4byte) ff_mult(11, p) << 24);

		it_tab[0][i] = t;
		it_tab[1][i] = rotl(t, 8);
		it_tab[2][i] = rotl(t, 16);
		it_tab[3][i] = rotl(t, 24);
	}

	tab_gen = 1;
#endif							/* !PRE_CALC_TABLES */
}