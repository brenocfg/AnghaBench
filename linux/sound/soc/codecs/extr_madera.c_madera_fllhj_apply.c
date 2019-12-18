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
struct madera_fll {int fout; scalar_t__ base; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int MADERA_FLL1_CLK_VCO_FAST_SRC_MASK ; 
 scalar_t__ MADERA_FLL1_DIGITAL_TEST_1_OFFS ; 
 int MADERA_FLL1_FB_DIV_MASK ; 
 int MADERA_FLL1_FB_DIV_SHIFT ; 
 int MADERA_FLL1_HP_MASK ; 
 int MADERA_FLL1_HP_SHIFT ; 
 int MADERA_FLL1_LAMBDA_MASK ; 
 unsigned int MADERA_FLL1_LAMBDA_SHIFT ; 
 int MADERA_FLL1_LOCKDET_THR_MASK ; 
 int MADERA_FLL1_LOCKDET_THR_SHIFT ; 
 unsigned int MADERA_FLL1_N_SHIFT ; 
 int MADERA_FLL1_PHASEDET_ENA_MASK ; 
 int MADERA_FLL1_PHASEDET_ENA_SHIFT ; 
 int MADERA_FLL1_REFCLK_DIV_MASK ; 
 int MADERA_FLL1_REFCLK_DIV_SHIFT ; 
 int MADERA_FLL1_SYNC_EFS_ENA_MASK ; 
 int MADERA_FLL1_THETA_MASK ; 
 unsigned int MADERA_FLL1_THETA_SHIFT ; 
 unsigned int MADERA_FLLHJ_FRAC_MAX_N ; 
 unsigned int MADERA_FLLHJ_FRAC_MIN_N ; 
 unsigned int MADERA_FLLHJ_HIGH_GAINS ; 
 unsigned int MADERA_FLLHJ_INT_MAX_N ; 
 unsigned int MADERA_FLLHJ_INT_MIN_N ; 
 unsigned int MADERA_FLLHJ_LOW_GAINS ; 
 int MADERA_FLLHJ_LOW_THRESH ; 
 int MADERA_FLLHJ_MAX_THRESH ; 
 unsigned int MADERA_FLLHJ_MID_GAINS ; 
 int MADERA_FLLHJ_MID_THRESH ; 
 scalar_t__ MADERA_FLL_CONTROL_10_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_11_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_2_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_3_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_4_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_5_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_6_OFFS ; 
 scalar_t__ MADERA_FLL_GAIN_OFFS ; 
 int gcd (int,int) ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  madera_fll_err (struct madera_fll*,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int madera_fllhj_apply(struct madera_fll *fll, int fin)
{
	struct madera *madera = fll->madera;
	int refdiv, fref, fout, lockdet_thr, fbdiv, hp, fast_clk, fllgcd;
	bool frac = false;
	unsigned int fll_n, min_n, max_n, ratio, theta, lambda;
	unsigned int gains, val, num;

	madera_fll_dbg(fll, "fin=%d, fout=%d\n", fin, fll->fout);

	for (refdiv = 0; refdiv < 4; refdiv++)
		if ((fin / (1 << refdiv)) <= MADERA_FLLHJ_MAX_THRESH)
			break;

	fref = fin / (1 << refdiv);

	/* Use simple heuristic approach to find a configuration that
	 * should work for most input clocks.
	 */
	fast_clk = 0;
	fout = fll->fout;
	frac = fout % fref;

	if (fref < MADERA_FLLHJ_LOW_THRESH) {
		lockdet_thr = 2;
		gains = MADERA_FLLHJ_LOW_GAINS;
		if (frac)
			fbdiv = 256;
		else
			fbdiv = 4;
	} else if (fref < MADERA_FLLHJ_MID_THRESH) {
		lockdet_thr = 8;
		gains = MADERA_FLLHJ_MID_GAINS;
		fbdiv = 1;
	} else {
		lockdet_thr = 8;
		gains = MADERA_FLLHJ_HIGH_GAINS;
		fbdiv = 1;
		/* For high speed input clocks, enable 300MHz fast oscillator
		 * when we're in fractional divider mode.
		 */
		if (frac) {
			fast_clk = 0x3;
			fout = fll->fout * 6;
		}
	}
	/* Use high performance mode for fractional configurations. */
	if (frac) {
		hp = 0x3;
		min_n = MADERA_FLLHJ_FRAC_MIN_N;
		max_n = MADERA_FLLHJ_FRAC_MAX_N;
	} else {
		hp = 0x0;
		min_n = MADERA_FLLHJ_INT_MIN_N;
		max_n = MADERA_FLLHJ_INT_MAX_N;
	}

	ratio = fout / fref;

	madera_fll_dbg(fll, "refdiv=%d, fref=%d, frac:%d\n",
		       refdiv, fref, frac);

	while (ratio / fbdiv < min_n) {
		fbdiv /= 2;
		if (fbdiv < 1) {
			madera_fll_err(fll, "FBDIV (%d) must be >= 1\n", fbdiv);
			return -EINVAL;
		}
	}
	while (frac && (ratio / fbdiv > max_n)) {
		fbdiv *= 2;
		if (fbdiv >= 1024) {
			madera_fll_err(fll, "FBDIV (%u) >= 1024\n", fbdiv);
			return -EINVAL;
		}
	}

	madera_fll_dbg(fll, "lockdet=%d, hp=0x%x, fbdiv:%d\n",
		       lockdet_thr, hp, fbdiv);

	/* Calculate N.K values */
	fllgcd = gcd(fout, fbdiv * fref);
	num = fout / fllgcd;
	lambda = (fref * fbdiv) / fllgcd;
	fll_n = num / lambda;
	theta = num % lambda;

	madera_fll_dbg(fll, "fll_n=%d, gcd=%d, theta=%d, lambda=%d\n",
		       fll_n, fllgcd, theta, lambda);

	/* Some sanity checks before any registers are written. */
	if (fll_n < min_n || fll_n > max_n) {
		madera_fll_err(fll, "N not in valid %s mode range %d-%d: %d\n",
			       frac ? "fractional" : "integer", min_n, max_n,
			       fll_n);
		return -EINVAL;
	}
	if (fbdiv < 1 || (frac && fbdiv >= 1024) || (!frac && fbdiv >= 256)) {
		madera_fll_err(fll, "Invalid fbdiv for %s mode (%u)\n",
			       frac ? "fractional" : "integer", fbdiv);
		return -EINVAL;
	}

	/* clear the ctrl_upd bit to guarantee we write to it later. */
	regmap_write(madera->regmap,
		     fll->base + MADERA_FLL_CONTROL_2_OFFS,
		     fll_n << MADERA_FLL1_N_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_3_OFFS,
			   MADERA_FLL1_THETA_MASK,
			   theta << MADERA_FLL1_THETA_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_4_OFFS,
			   MADERA_FLL1_LAMBDA_MASK,
			   lambda << MADERA_FLL1_LAMBDA_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_5_OFFS,
			   MADERA_FLL1_FB_DIV_MASK,
			   fbdiv << MADERA_FLL1_FB_DIV_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_6_OFFS,
			   MADERA_FLL1_REFCLK_DIV_MASK,
			   refdiv << MADERA_FLL1_REFCLK_DIV_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_GAIN_OFFS,
			   0xffff,
			   gains);
	val = hp << MADERA_FLL1_HP_SHIFT;
	val |= 1 << MADERA_FLL1_PHASEDET_ENA_SHIFT;
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_10_OFFS,
			   MADERA_FLL1_HP_MASK | MADERA_FLL1_PHASEDET_ENA_MASK,
			   val);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_11_OFFS,
			   MADERA_FLL1_LOCKDET_THR_MASK,
			   lockdet_thr << MADERA_FLL1_LOCKDET_THR_SHIFT);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL1_DIGITAL_TEST_1_OFFS,
			   MADERA_FLL1_SYNC_EFS_ENA_MASK |
			   MADERA_FLL1_CLK_VCO_FAST_SRC_MASK,
			   fast_clk);

	return 0;
}