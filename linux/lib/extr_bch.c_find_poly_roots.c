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
struct gf_poly {int deg; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 unsigned int GF_M (struct bch_control*) ; 
 int /*<<< orphan*/  factor_polynomial (struct bch_control*,unsigned int,struct gf_poly*,struct gf_poly**,struct gf_poly**) ; 
 int find_poly_deg1_roots (struct bch_control*,struct gf_poly*,unsigned int*) ; 
 int find_poly_deg2_roots (struct bch_control*,struct gf_poly*,unsigned int*) ; 
 int find_poly_deg3_roots (struct bch_control*,struct gf_poly*,unsigned int*) ; 
 int find_poly_deg4_roots (struct bch_control*,struct gf_poly*,unsigned int*) ; 

__attribute__((used)) static int find_poly_roots(struct bch_control *bch, unsigned int k,
			   struct gf_poly *poly, unsigned int *roots)
{
	int cnt;
	struct gf_poly *f1, *f2;

	switch (poly->deg) {
		/* handle low degree polynomials with ad hoc techniques */
	case 1:
		cnt = find_poly_deg1_roots(bch, poly, roots);
		break;
	case 2:
		cnt = find_poly_deg2_roots(bch, poly, roots);
		break;
	case 3:
		cnt = find_poly_deg3_roots(bch, poly, roots);
		break;
	case 4:
		cnt = find_poly_deg4_roots(bch, poly, roots);
		break;
	default:
		/* factor polynomial using Berlekamp Trace Algorithm (BTA) */
		cnt = 0;
		if (poly->deg && (k <= GF_M(bch))) {
			factor_polynomial(bch, k, poly, &f1, &f2);
			if (f1)
				cnt += find_poly_roots(bch, k+1, f1, roots);
			if (f2)
				cnt += find_poly_roots(bch, k+1, f2, roots+cnt);
		}
		break;
	}
	return cnt;
}