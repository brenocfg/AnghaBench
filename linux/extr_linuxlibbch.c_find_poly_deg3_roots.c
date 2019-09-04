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
struct gf_poly {int* c; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 unsigned int a_ilog (struct bch_control*,unsigned int) ; 
 int find_affine4_roots (struct bch_control*,unsigned int,unsigned int,unsigned int,unsigned int*) ; 
 unsigned int gf_div (struct bch_control*,unsigned int,unsigned int) ; 
 unsigned int gf_mul (struct bch_control*,unsigned int,unsigned int) ; 
 unsigned int gf_sqr (struct bch_control*,unsigned int) ; 

__attribute__((used)) static int find_poly_deg3_roots(struct bch_control *bch, struct gf_poly *poly,
				unsigned int *roots)
{
	int i, n = 0;
	unsigned int a, b, c, a2, b2, c2, e3, tmp[4];

	if (poly->c[0]) {
		/* transform polynomial into monic X^3 + a2X^2 + b2X + c2 */
		e3 = poly->c[3];
		c2 = gf_div(bch, poly->c[0], e3);
		b2 = gf_div(bch, poly->c[1], e3);
		a2 = gf_div(bch, poly->c[2], e3);

		/* (X+a2)(X^3+a2X^2+b2X+c2) = X^4+aX^2+bX+c (affine) */
		c = gf_mul(bch, a2, c2);           /* c = a2c2      */
		b = gf_mul(bch, a2, b2)^c2;        /* b = a2b2 + c2 */
		a = gf_sqr(bch, a2)^b2;            /* a = a2^2 + b2 */

		/* find the 4 roots of this affine polynomial */
		if (find_affine4_roots(bch, a, b, c, tmp) == 4) {
			/* remove a2 from final list of roots */
			for (i = 0; i < 4; i++) {
				if (tmp[i] != a2)
					roots[n++] = a_ilog(bch, tmp[i]);
			}
		}
	}
	return n;
}