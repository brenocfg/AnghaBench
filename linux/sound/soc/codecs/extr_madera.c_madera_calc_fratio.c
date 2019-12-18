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
struct madera_fll_cfg {int refdiv; int fratio; } ;
struct madera_fll {int fout; TYPE_1__* madera; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
#define  CS47L35 130 
#define  CS47L85 129 
 int EINVAL ; 
 int MADERA_FLL_MAX_FRATIO ; 
 unsigned int MADERA_FLL_MAX_FREF ; 
 int MADERA_FLL_MAX_REFDIV ; 
 int MADERA_FLL_VCO_CORNER ; 
 int MADERA_FLL_VCO_MULT ; 
#define  WM1840 128 
 int madera_find_fratio (struct madera_fll*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  madera_fll_err (struct madera_fll*,char*,unsigned int) ; 
 int /*<<< orphan*/  madera_fll_warn (struct madera_fll*,char*) ; 
 unsigned int* pseudo_fref_max ; 

__attribute__((used)) static int madera_calc_fratio(struct madera_fll *fll,
			      struct madera_fll_cfg *cfg,
			      unsigned int fref, bool sync)
{
	int init_ratio, ratio;
	int refdiv, div;

	/* fref must be <=13.5MHz, find initial refdiv */
	div = 1;
	cfg->refdiv = 0;
	while (fref > MADERA_FLL_MAX_FREF) {
		div *= 2;
		fref /= 2;
		cfg->refdiv++;

		if (div > MADERA_FLL_MAX_REFDIV)
			return -EINVAL;
	}

	/* Find an appropriate FLL_FRATIO */
	init_ratio = madera_find_fratio(fll, fref, sync, &cfg->fratio);
	if (init_ratio < 0) {
		madera_fll_err(fll, "Unable to find FRATIO for fref=%uHz\n",
			       fref);
		return init_ratio;
	}

	if (!sync)
		cfg->fratio = init_ratio - 1;

	switch (fll->madera->type) {
	case CS47L35:
		switch (fll->madera->rev) {
		case 0:
			if (sync)
				return init_ratio;
			break;
		default:
			return init_ratio;
		}
		break;
	case CS47L85:
	case WM1840:
		if (sync)
			return init_ratio;
		break;
	default:
		return init_ratio;
	}

	/*
	 * For CS47L35 rev A0, CS47L85 and WM1840 adjust FRATIO/refdiv to avoid
	 * integer mode if possible
	 */
	refdiv = cfg->refdiv;

	while (div <= MADERA_FLL_MAX_REFDIV) {
		/*
		 * start from init_ratio because this may already give a
		 * fractional N.K
		 */
		for (ratio = init_ratio; ratio > 0; ratio--) {
			if (fll->fout % (ratio * fref)) {
				cfg->refdiv = refdiv;
				cfg->fratio = ratio - 1;
				return ratio;
			}
		}

		for (ratio = init_ratio + 1; ratio <= MADERA_FLL_MAX_FRATIO;
		     ratio++) {
			if ((MADERA_FLL_VCO_CORNER / 2) /
			    (MADERA_FLL_VCO_MULT * ratio) < fref)
				break;

			if (fref > pseudo_fref_max[ratio - 1])
				break;

			if (fll->fout % (ratio * fref)) {
				cfg->refdiv = refdiv;
				cfg->fratio = ratio - 1;
				return ratio;
			}
		}

		div *= 2;
		fref /= 2;
		refdiv++;
		init_ratio = madera_find_fratio(fll, fref, sync, NULL);
	}

	madera_fll_warn(fll, "Falling back to integer mode operation\n");

	return cfg->fratio + 1;
}