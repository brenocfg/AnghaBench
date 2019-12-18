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
struct madera_fll_gains {int dummy; } ;
struct madera_fll_cfg {int refdiv; int n; int theta; int lambda; int gain; int /*<<< orphan*/  fratio; } ;
struct madera_fll {int fout; TYPE_1__* madera; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct madera_fll_gains*) ; 
#define  CS47L35 130 
#define  CS47L85 129 
 int MADERA_FLL_VCO_MULT ; 
#define  WM1840 128 
 unsigned int gcd (int,int) ; 
 int madera_calc_fratio (struct madera_fll*,struct madera_fll_cfg*,unsigned int,int) ; 
 int madera_find_fll_gain (struct madera_fll*,struct madera_fll_cfg*,unsigned int,struct madera_fll_gains const*,int) ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*,int,...) ; 
 struct madera_fll_gains* madera_fll_main_gains ; 
 struct madera_fll_gains* madera_fll_sync_gains ; 

__attribute__((used)) static int madera_calc_fll(struct madera_fll *fll,
			   struct madera_fll_cfg *cfg,
			   unsigned int fref, bool sync)
{
	unsigned int gcd_fll;
	const struct madera_fll_gains *gains;
	int n_gains;
	int ratio, ret;

	madera_fll_dbg(fll, "fref=%u Fout=%u fvco=%u\n",
		       fref, fll->fout, fll->fout * MADERA_FLL_VCO_MULT);

	/* Find an appropriate FLL_FRATIO and refdiv */
	ratio = madera_calc_fratio(fll, cfg, fref, sync);
	if (ratio < 0)
		return ratio;

	/* Apply the division for our remaining calculations */
	fref = fref / (1 << cfg->refdiv);

	cfg->n = fll->fout / (ratio * fref);

	if (fll->fout % (ratio * fref)) {
		gcd_fll = gcd(fll->fout, ratio * fref);
		madera_fll_dbg(fll, "GCD=%u\n", gcd_fll);

		cfg->theta = (fll->fout - (cfg->n * ratio * fref))
			/ gcd_fll;
		cfg->lambda = (ratio * fref) / gcd_fll;
	} else {
		cfg->theta = 0;
		cfg->lambda = 0;
	}

	/*
	 * Round down to 16bit range with cost of accuracy lost.
	 * Denominator must be bigger than numerator so we only
	 * take care of it.
	 */
	while (cfg->lambda >= (1 << 16)) {
		cfg->theta >>= 1;
		cfg->lambda >>= 1;
	}

	switch (fll->madera->type) {
	case CS47L35:
		switch (fll->madera->rev) {
		case 0:
			/* Rev A0 uses the sync gains for both loops */
			gains = madera_fll_sync_gains;
			n_gains = ARRAY_SIZE(madera_fll_sync_gains);
			break;
		default:
			if (sync) {
				gains = madera_fll_sync_gains;
				n_gains = ARRAY_SIZE(madera_fll_sync_gains);
			} else {
				gains = madera_fll_main_gains;
				n_gains = ARRAY_SIZE(madera_fll_main_gains);
			}
			break;
		}
		break;
	case CS47L85:
	case WM1840:
		/* These use the sync gains for both loops */
		gains = madera_fll_sync_gains;
		n_gains = ARRAY_SIZE(madera_fll_sync_gains);
		break;
	default:
		if (sync) {
			gains = madera_fll_sync_gains;
			n_gains = ARRAY_SIZE(madera_fll_sync_gains);
		} else {
			gains = madera_fll_main_gains;
			n_gains = ARRAY_SIZE(madera_fll_main_gains);
		}
		break;
	}

	ret = madera_find_fll_gain(fll, cfg, fref, gains, n_gains);
	if (ret)
		return ret;

	madera_fll_dbg(fll, "N=%d THETA=%d LAMBDA=%d\n",
		       cfg->n, cfg->theta, cfg->lambda);
	madera_fll_dbg(fll, "FRATIO=0x%x(%d) REFCLK_DIV=0x%x(%d)\n",
		       cfg->fratio, ratio, cfg->refdiv, 1 << cfg->refdiv);
	madera_fll_dbg(fll, "GAIN=0x%x(%d)\n", cfg->gain, 1 << cfg->gain);

	return 0;
}