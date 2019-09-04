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
typedef  int /*<<< orphan*/  uint32_t ;
struct gf_poly_deg1 {int dummy; } ;
struct bch_control {int m; int t; int n; void** poly_2t; void* elp; void* cache; void* syn; void* xi_tab; void* ecc_buf2; void* ecc_buf; void* mod8_tab; void* a_log_tab; void* a_pow_tab; void* ecc_bytes; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (void**) ; 
 int BCH_MAX_M ; 
 int BCH_MAX_T ; 
 void* DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GF_POLY_SZ (int) ; 
 void* bch_alloc (int,int*) ; 
 int build_deg2_base (struct bch_control*) ; 
 int build_gf_tables (struct bch_control*,unsigned int) ; 
 int /*<<< orphan*/  build_mod8_tables (struct bch_control*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compute_generator_polynomial (struct bch_control*) ; 
 int /*<<< orphan*/  free_bch (struct bch_control*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct bch_control* kzalloc (int,int /*<<< orphan*/ ) ; 

struct bch_control *init_bch(int m, int t, unsigned int prim_poly)
{
	int err = 0;
	unsigned int i, words;
	uint32_t *genpoly;
	struct bch_control *bch = NULL;

	const int min_m = 5;

	/* default primitive polynomials */
	static const unsigned int prim_poly_tab[] = {
		0x25, 0x43, 0x83, 0x11d, 0x211, 0x409, 0x805, 0x1053, 0x201b,
		0x402b, 0x8003,
	};

#if defined(CONFIG_BCH_CONST_PARAMS)
	if ((m != (CONFIG_BCH_CONST_M)) || (t != (CONFIG_BCH_CONST_T))) {
		printk(KERN_ERR "bch encoder/decoder was configured to support "
		       "parameters m=%d, t=%d only!\n",
		       CONFIG_BCH_CONST_M, CONFIG_BCH_CONST_T);
		goto fail;
	}
#endif
	if ((m < min_m) || (m > BCH_MAX_M))
		/*
		 * values of m greater than 15 are not currently supported;
		 * supporting m > 15 would require changing table base type
		 * (uint16_t) and a small patch in matrix transposition
		 */
		goto fail;

	if (t > BCH_MAX_T)
		/*
		 * we can support larger than 64 bits if necessary, at the
		 * cost of higher stack usage.
		 */
		goto fail;

	/* sanity checks */
	if ((t < 1) || (m*t >= ((1 << m)-1)))
		/* invalid t value */
		goto fail;

	/* select a primitive polynomial for generating GF(2^m) */
	if (prim_poly == 0)
		prim_poly = prim_poly_tab[m-min_m];

	bch = kzalloc(sizeof(*bch), GFP_KERNEL);
	if (bch == NULL)
		goto fail;

	bch->m = m;
	bch->t = t;
	bch->n = (1 << m)-1;
	words  = DIV_ROUND_UP(m*t, 32);
	bch->ecc_bytes = DIV_ROUND_UP(m*t, 8);
	bch->a_pow_tab = bch_alloc((1+bch->n)*sizeof(*bch->a_pow_tab), &err);
	bch->a_log_tab = bch_alloc((1+bch->n)*sizeof(*bch->a_log_tab), &err);
	bch->mod8_tab  = bch_alloc(words*1024*sizeof(*bch->mod8_tab), &err);
	bch->ecc_buf   = bch_alloc(words*sizeof(*bch->ecc_buf), &err);
	bch->ecc_buf2  = bch_alloc(words*sizeof(*bch->ecc_buf2), &err);
	bch->xi_tab    = bch_alloc(m*sizeof(*bch->xi_tab), &err);
	bch->syn       = bch_alloc(2*t*sizeof(*bch->syn), &err);
	bch->cache     = bch_alloc(2*t*sizeof(*bch->cache), &err);
	bch->elp       = bch_alloc((t+1)*sizeof(struct gf_poly_deg1), &err);

	for (i = 0; i < ARRAY_SIZE(bch->poly_2t); i++)
		bch->poly_2t[i] = bch_alloc(GF_POLY_SZ(2*t), &err);

	if (err)
		goto fail;

	err = build_gf_tables(bch, prim_poly);
	if (err)
		goto fail;

	/* use generator polynomial for computing encoding tables */
	genpoly = compute_generator_polynomial(bch);
	if (genpoly == NULL)
		goto fail;

	build_mod8_tables(bch, genpoly);
	kfree(genpoly);

	err = build_deg2_base(bch);
	if (err)
		goto fail;

	return bch;

fail:
	free_bch(bch);
	return NULL;
}