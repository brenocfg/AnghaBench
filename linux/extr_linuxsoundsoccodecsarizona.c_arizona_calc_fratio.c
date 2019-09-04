#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct arizona_fll_cfg {int refdiv; int fratio; } ;
struct arizona_fll {int vco_mult; TYPE_1__* arizona; } ;
struct TYPE_2__ {int type; int rev; } ;

/* Variables and functions */
 int ARIZONA_FLL_MAX_FRATIO ; 
 unsigned int ARIZONA_FLL_MAX_FREF ; 
 int ARIZONA_FLL_MAX_REFDIV ; 
 int ARIZONA_FLL_VCO_CORNER ; 
 int EINVAL ; 
#define  WM5102 131 
#define  WM5110 130 
#define  WM8280 129 
#define  WM8997 128 
 int arizona_find_fratio (unsigned int,int*) ; 
 int /*<<< orphan*/  arizona_fll_dbg (struct arizona_fll*,char*,...) ; 
 int /*<<< orphan*/  arizona_fll_err (struct arizona_fll*,char*,unsigned int) ; 
 int /*<<< orphan*/  arizona_fll_warn (struct arizona_fll*,char*) ; 
 unsigned int* pseudo_fref_max ; 

__attribute__((used)) static int arizona_calc_fratio(struct arizona_fll *fll,
			       struct arizona_fll_cfg *cfg,
			       unsigned int target,
			       unsigned int Fref, bool sync)
{
	int init_ratio, ratio;
	int refdiv, div;

	/* Fref must be <=13.5MHz, find initial refdiv */
	div = 1;
	cfg->refdiv = 0;
	while (Fref > ARIZONA_FLL_MAX_FREF) {
		div *= 2;
		Fref /= 2;
		cfg->refdiv++;

		if (div > ARIZONA_FLL_MAX_REFDIV)
			return -EINVAL;
	}

	/* Find an appropriate FLL_FRATIO */
	init_ratio = arizona_find_fratio(Fref, &cfg->fratio);
	if (init_ratio < 0) {
		arizona_fll_err(fll, "Unable to find FRATIO for Fref=%uHz\n",
				Fref);
		return init_ratio;
	}

	switch (fll->arizona->type) {
	case WM5102:
	case WM8997:
		return init_ratio;
	case WM5110:
	case WM8280:
		if (fll->arizona->rev < 3 || sync)
			return init_ratio;
		break;
	default:
		if (sync)
			return init_ratio;
		break;
	}

	cfg->fratio = init_ratio - 1;

	/* Adjust FRATIO/refdiv to avoid integer mode if possible */
	refdiv = cfg->refdiv;

	arizona_fll_dbg(fll, "pseudo: initial ratio=%u fref=%u refdiv=%u\n",
			init_ratio, Fref, refdiv);

	while (div <= ARIZONA_FLL_MAX_REFDIV) {
		/* start from init_ratio because this may already give a
		 * fractional N.K
		 */
		for (ratio = init_ratio; ratio > 0; ratio--) {
			if (target % (ratio * Fref)) {
				cfg->refdiv = refdiv;
				cfg->fratio = ratio - 1;
				arizona_fll_dbg(fll,
					"pseudo: found fref=%u refdiv=%d(%d) ratio=%d\n",
					Fref, refdiv, div, ratio);
				return ratio;
			}
		}

		for (ratio = init_ratio + 1; ratio <= ARIZONA_FLL_MAX_FRATIO;
		     ratio++) {
			if ((ARIZONA_FLL_VCO_CORNER / 2) /
			    (fll->vco_mult * ratio) < Fref) {
				arizona_fll_dbg(fll, "pseudo: hit VCO corner\n");
				break;
			}

			if (Fref > pseudo_fref_max[ratio - 1]) {
				arizona_fll_dbg(fll,
					"pseudo: exceeded max fref(%u) for ratio=%u\n",
					pseudo_fref_max[ratio - 1],
					ratio);
				break;
			}

			if (target % (ratio * Fref)) {
				cfg->refdiv = refdiv;
				cfg->fratio = ratio - 1;
				arizona_fll_dbg(fll,
					"pseudo: found fref=%u refdiv=%d(%d) ratio=%d\n",
					Fref, refdiv, div, ratio);
				return ratio;
			}
		}

		div *= 2;
		Fref /= 2;
		refdiv++;
		init_ratio = arizona_find_fratio(Fref, NULL);
		arizona_fll_dbg(fll,
				"pseudo: change fref=%u refdiv=%d(%d) ratio=%u\n",
				Fref, refdiv, div, init_ratio);
	}

	arizona_fll_warn(fll, "Falling back to integer mode operation\n");
	return cfg->fratio + 1;
}