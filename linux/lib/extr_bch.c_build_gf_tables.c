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
struct bch_control {unsigned int* a_pow_tab; unsigned int* a_log_tab; } ;

/* Variables and functions */
 unsigned int GF_M (struct bch_control*) ; 
 size_t GF_N (struct bch_control*) ; 
 int deg (unsigned int) ; 

__attribute__((used)) static int build_gf_tables(struct bch_control *bch, unsigned int poly)
{
	unsigned int i, x = 1;
	const unsigned int k = 1 << deg(poly);

	/* primitive polynomial must be of degree m */
	if (k != (1u << GF_M(bch)))
		return -1;

	for (i = 0; i < GF_N(bch); i++) {
		bch->a_pow_tab[i] = x;
		bch->a_log_tab[x] = i;
		if (i && (x == 1))
			/* polynomial is not primitive (a^i=1 with 0<i<2^m-1) */
			return -1;
		x <<= 1;
		if (x & k)
			x ^= poly;
	}
	bch->a_pow_tab[GF_N(bch)] = 1;
	bch->a_log_tab[0] = 0;

	return 0;
}