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
struct bch_control {int* mod8_tab; scalar_t__ ecc_bits; } ;

/* Variables and functions */
 int BCH_ECC_WORDS (struct bch_control*) ; 
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int deg (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void build_mod8_tables(struct bch_control *bch, const uint32_t *g)
{
	int i, j, b, d;
	uint32_t data, hi, lo, *tab;
	const int l = BCH_ECC_WORDS(bch);
	const int plen = DIV_ROUND_UP(bch->ecc_bits+1, 32);
	const int ecclen = DIV_ROUND_UP(bch->ecc_bits, 32);

	memset(bch->mod8_tab, 0, 4*256*l*sizeof(*bch->mod8_tab));

	for (i = 0; i < 256; i++) {
		/* p(X)=i is a small polynomial of weight <= 8 */
		for (b = 0; b < 4; b++) {
			/* we want to compute (p(X).X^(8*b+deg(g))) mod g(X) */
			tab = bch->mod8_tab + (b*256+i)*l;
			data = i << (8*b);
			while (data) {
				d = deg(data);
				/* subtract X^d.g(X) from p(X).X^(8*b+deg(g)) */
				data ^= g[0] >> (31-d);
				for (j = 0; j < ecclen; j++) {
					hi = (d < 31) ? g[j] << (d+1) : 0;
					lo = (j+1 < plen) ?
						g[j+1] >> (31-d) : 0;
					tab[j] ^= hi|lo;
				}
			}
		}
	}
}