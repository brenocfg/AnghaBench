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
struct gf_poly {unsigned int* c; unsigned int deg; } ;
struct bch_control {int* cache; unsigned int* a_pow_tab; } ;

/* Variables and functions */
 int a_log (struct bch_control*,unsigned int) ; 
 int /*<<< orphan*/  gf_poly_logrep (struct bch_control*,struct gf_poly const*,int*) ; 
 size_t mod_s (struct bch_control*,int) ; 

__attribute__((used)) static void gf_poly_mod(struct bch_control *bch, struct gf_poly *a,
			const struct gf_poly *b, int *rep)
{
	int la, p, m;
	unsigned int i, j, *c = a->c;
	const unsigned int d = b->deg;

	if (a->deg < d)
		return;

	/* reuse or compute log representation of denominator */
	if (!rep) {
		rep = bch->cache;
		gf_poly_logrep(bch, b, rep);
	}

	for (j = a->deg; j >= d; j--) {
		if (c[j]) {
			la = a_log(bch, c[j]);
			p = j-d;
			for (i = 0; i < d; i++, p++) {
				m = rep[i];
				if (m >= 0)
					c[p] ^= bch->a_pow_tab[mod_s(bch,
								     m+la)];
			}
		}
	}
	a->deg = d-1;
	while (!c[a->deg] && a->deg)
		a->deg--;
}