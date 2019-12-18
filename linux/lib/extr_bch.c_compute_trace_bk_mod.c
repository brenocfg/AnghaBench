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
struct gf_poly {int deg; int /*<<< orphan*/ * c; } ;
struct bch_control {int /*<<< orphan*/  cache; int /*<<< orphan*/ * a_pow_tab; } ;

/* Variables and functions */
 int GF_M (struct bch_control*) ; 
 int /*<<< orphan*/  GF_POLY_SZ (int) ; 
 int /*<<< orphan*/  dbg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_poly_logrep (struct bch_control*,struct gf_poly const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_poly_mod (struct bch_control*,struct gf_poly*,struct gf_poly const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_poly_str (struct gf_poly*) ; 
 int /*<<< orphan*/  gf_sqr (struct bch_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gf_poly*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compute_trace_bk_mod(struct bch_control *bch, int k,
				 const struct gf_poly *f, struct gf_poly *z,
				 struct gf_poly *out)
{
	const int m = GF_M(bch);
	int i, j;

	/* z contains z^2j mod f */
	z->deg = 1;
	z->c[0] = 0;
	z->c[1] = bch->a_pow_tab[k];

	out->deg = 0;
	memset(out, 0, GF_POLY_SZ(f->deg));

	/* compute f log representation only once */
	gf_poly_logrep(bch, f, bch->cache);

	for (i = 0; i < m; i++) {
		/* add a^(k*2^i)(z^(2^i) mod f) and compute (z^(2^i) mod f)^2 */
		for (j = z->deg; j >= 0; j--) {
			out->c[j] ^= z->c[j];
			z->c[2*j] = gf_sqr(bch, z->c[j]);
			z->c[2*j+1] = 0;
		}
		if (z->deg > out->deg)
			out->deg = z->deg;

		if (i < m-1) {
			z->deg *= 2;
			/* z^(2(i+1)) mod f = (z^(2^i) mod f)^2 mod f */
			gf_poly_mod(bch, z, f, bch->cache);
		}
	}
	while (!out->c[out->deg] && out->deg)
		out->deg--;

	dbg("Tr(a^%d.X) mod f = %s\n", k, gf_poly_str(out));
}