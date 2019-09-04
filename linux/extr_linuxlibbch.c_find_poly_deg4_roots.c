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
struct gf_poly {unsigned int* c; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 int GF_N (struct bch_control*) ; 
 unsigned int a_ilog (struct bch_control*,unsigned int) ; 
 int a_log (struct bch_control*,unsigned int) ; 
 unsigned int a_pow (struct bch_control*,int) ; 
 int find_affine4_roots (struct bch_control*,unsigned int,unsigned int,unsigned int,unsigned int*) ; 
 unsigned int gf_div (struct bch_control*,unsigned int,unsigned int) ; 
 unsigned int gf_inv (struct bch_control*,unsigned int) ; 
 unsigned int gf_mul (struct bch_control*,unsigned int,unsigned int) ; 

__attribute__((used)) static int find_poly_deg4_roots(struct bch_control *bch, struct gf_poly *poly,
				unsigned int *roots)
{
	int i, l, n = 0;
	unsigned int a, b, c, d, e = 0, f, a2, b2, c2, e4;

	if (poly->c[0] == 0)
		return 0;

	/* transform polynomial into monic X^4 + aX^3 + bX^2 + cX + d */
	e4 = poly->c[4];
	d = gf_div(bch, poly->c[0], e4);
	c = gf_div(bch, poly->c[1], e4);
	b = gf_div(bch, poly->c[2], e4);
	a = gf_div(bch, poly->c[3], e4);

	/* use Y=1/X transformation to get an affine polynomial */
	if (a) {
		/* first, eliminate cX by using z=X+e with ae^2+c=0 */
		if (c) {
			/* compute e such that e^2 = c/a */
			f = gf_div(bch, c, a);
			l = a_log(bch, f);
			l += (l & 1) ? GF_N(bch) : 0;
			e = a_pow(bch, l/2);
			/*
			 * use transformation z=X+e:
			 * z^4+e^4 + a(z^3+ez^2+e^2z+e^3) + b(z^2+e^2) +cz+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + (ae^2+c)z+e^4+be^2+ae^3+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + e^4+be^2+d
			 * z^4 + az^3 +     b'z^2 + d'
			 */
			d = a_pow(bch, 2*l)^gf_mul(bch, b, f)^d;
			b = gf_mul(bch, a, e)^b;
		}
		/* now, use Y=1/X to get Y^4 + b/dY^2 + a/dY + 1/d */
		if (d == 0)
			/* assume all roots have multiplicity 1 */
			return 0;

		c2 = gf_inv(bch, d);
		b2 = gf_div(bch, a, d);
		a2 = gf_div(bch, b, d);
	} else {
		/* polynomial is already affine */
		c2 = d;
		b2 = c;
		a2 = b;
	}
	/* find the 4 roots of this affine polynomial */
	if (find_affine4_roots(bch, a2, b2, c2, roots) == 4) {
		for (i = 0; i < 4; i++) {
			/* post-process roots (reverse transformations) */
			f = a ? gf_inv(bch, roots[i]) : roots[i];
			roots[i] = a_ilog(bch, f^e);
		}
		n = 4;
	}
	return n;
}