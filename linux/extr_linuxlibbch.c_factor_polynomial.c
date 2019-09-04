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
struct gf_poly {scalar_t__ deg; } ;
struct gf_poly_deg1 {struct gf_poly poly; } ;
struct bch_control {struct gf_poly** poly_2t; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_trace_bk_mod (struct bch_control*,int,struct gf_poly*,struct gf_poly*,struct gf_poly*) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_poly_copy (struct gf_poly*,struct gf_poly*) ; 
 int /*<<< orphan*/  gf_poly_div (struct bch_control*,struct gf_poly*,struct gf_poly*,struct gf_poly*) ; 
 struct gf_poly* gf_poly_gcd (struct bch_control*,struct gf_poly*,struct gf_poly*) ; 
 int /*<<< orphan*/  gf_poly_str (struct gf_poly*) ; 

__attribute__((used)) static void factor_polynomial(struct bch_control *bch, int k, struct gf_poly *f,
			      struct gf_poly **g, struct gf_poly **h)
{
	struct gf_poly *f2 = bch->poly_2t[0];
	struct gf_poly *q  = bch->poly_2t[1];
	struct gf_poly *tk = bch->poly_2t[2];
	struct gf_poly *z  = bch->poly_2t[3];
	struct gf_poly *gcd;

	dbg("factoring %s...\n", gf_poly_str(f));

	*g = f;
	*h = NULL;

	/* tk = Tr(a^k.X) mod f */
	compute_trace_bk_mod(bch, k, f, z, tk);

	if (tk->deg > 0) {
		/* compute g = gcd(f, tk) (destructive operation) */
		gf_poly_copy(f2, f);
		gcd = gf_poly_gcd(bch, f2, tk);
		if (gcd->deg < f->deg) {
			/* compute h=f/gcd(f,tk); this will modify f and q */
			gf_poly_div(bch, f, gcd, q);
			/* store g and h in-place (clobbering f) */
			*h = &((struct gf_poly_deg1 *)f)[gcd->deg].poly;
			gf_poly_copy(*g, gcd);
			gf_poly_copy(*h, q);
		}
	}
}