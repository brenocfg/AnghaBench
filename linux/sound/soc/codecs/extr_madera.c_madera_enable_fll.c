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
struct madera_fll_cfg {int gain; int lambda; int theta; int alt_gain; } ;
struct madera_fll {unsigned int base; scalar_t__ ref_src; scalar_t__ ref_freq; scalar_t__ fout; scalar_t__ sync_src; scalar_t__ sync_freq; struct madera* madera; } ;
struct madera {int type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
#define  CS47L35 130 
 int /*<<< orphan*/  CS47L35_FLL_SYNCHRONISER_OFFS ; 
#define  CS47L85 129 
 int EINVAL ; 
 int /*<<< orphan*/  MADERA_FLL1_ENA ; 
 int /*<<< orphan*/  MADERA_FLL1_FREERUN ; 
 int /*<<< orphan*/  MADERA_FLL1_GAIN_MASK ; 
 int /*<<< orphan*/  MADERA_FLL1_SYNC_DFSAT ; 
 int /*<<< orphan*/  MADERA_FLL1_SYNC_DFSAT_MASK ; 
 int /*<<< orphan*/  MADERA_FLL1_SYNC_ENA ; 
 scalar_t__ MADERA_FLL_CONTROL_1_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_7_OFFS ; 
 scalar_t__ MADERA_FLL_MAX_FOUT ; 
 scalar_t__ MADERA_FLL_MIN_FOUT ; 
 scalar_t__ MADERA_FLL_SYNCHRONISER_1_OFFS ; 
 scalar_t__ MADERA_FLL_SYNCHRONISER_7_OFFS ; 
 int /*<<< orphan*/  MADERA_FLL_SYNCHRONISER_OFFS ; 
#define  WM1840 128 
 int madera_calc_fll (struct madera_fll*,struct madera_fll_cfg*,scalar_t__,int) ; 
 int /*<<< orphan*/  madera_disable_fll (struct madera_fll*) ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*,char*) ; 
 int /*<<< orphan*/  madera_fll_err (struct madera_fll*,char*,...) ; 
 int /*<<< orphan*/  madera_fll_warn (struct madera_fll*,char*) ; 
 int madera_is_enabled_fll (struct madera_fll*,unsigned int) ; 
 int madera_set_fll_phase_integrator (struct madera_fll*,struct madera_fll_cfg*,int) ; 
 int /*<<< orphan*/  madera_wait_for_fll (struct madera_fll*,int) ; 
 int madera_write_fll (struct madera*,unsigned int,struct madera_fll_cfg*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int madera_enable_fll(struct madera_fll *fll)
{
	struct madera *madera = fll->madera;
	bool have_sync = false;
	int already_enabled = madera_is_enabled_fll(fll, fll->base);
	int sync_enabled;
	struct madera_fll_cfg cfg;
	unsigned int sync_base;
	int gain, ret;
	bool fll_change = false;

	if (already_enabled < 0)
		return already_enabled;	/* error getting current state */

	if (fll->ref_src < 0 || fll->ref_freq == 0) {
		madera_fll_err(fll, "No REFCLK\n");
		ret = -EINVAL;
		goto err;
	}

	madera_fll_dbg(fll, "Enabling FLL, initially %s\n",
		       already_enabled ? "enabled" : "disabled");

	if (fll->fout < MADERA_FLL_MIN_FOUT ||
	    fll->fout > MADERA_FLL_MAX_FOUT) {
		madera_fll_err(fll, "invalid fout %uHz\n", fll->fout);
		ret = -EINVAL;
		goto err;
	}

	switch (madera->type) {
	case CS47L35:
		sync_base = fll->base + CS47L35_FLL_SYNCHRONISER_OFFS;
		break;
	default:
		sync_base = fll->base + MADERA_FLL_SYNCHRONISER_OFFS;
		break;
	}

	sync_enabled = madera_is_enabled_fll(fll, sync_base);
	if (sync_enabled < 0)
		return sync_enabled;

	if (already_enabled) {
		/* Facilitate smooth refclk across the transition */
		regmap_update_bits(fll->madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_1_OFFS,
				   MADERA_FLL1_FREERUN,
				   MADERA_FLL1_FREERUN);
		udelay(32);
		regmap_update_bits(fll->madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_7_OFFS,
				   MADERA_FLL1_GAIN_MASK, 0);
	}

	/* Apply SYNCCLK setting */
	if (fll->sync_src >= 0) {
		ret = madera_calc_fll(fll, &cfg, fll->sync_freq, true);
		if (ret < 0)
			goto err;

		fll_change |= madera_write_fll(madera, sync_base,
					       &cfg, fll->sync_src,
					       true, cfg.gain);
		have_sync = true;
	}

	if (already_enabled && !!sync_enabled != have_sync)
		madera_fll_warn(fll, "Synchroniser changed on active FLL\n");

	/* Apply REFCLK setting */
	ret = madera_calc_fll(fll, &cfg, fll->ref_freq, false);
	if (ret < 0)
		goto err;

	/* Ref path hardcodes lambda to 65536 when sync is on */
	if (have_sync && cfg.lambda)
		cfg.theta = (cfg.theta * (1 << 16)) / cfg.lambda;

	switch (fll->madera->type) {
	case CS47L35:
		switch (fll->madera->rev) {
		case 0:
			gain = cfg.gain;
			break;
		default:
			fll_change |=
				madera_set_fll_phase_integrator(fll, &cfg,
								have_sync);
			if (!have_sync && cfg.theta == 0)
				gain = cfg.alt_gain;
			else
				gain = cfg.gain;
			break;
		}
		break;
	case CS47L85:
	case WM1840:
		gain = cfg.gain;
		break;
	default:
		fll_change |= madera_set_fll_phase_integrator(fll, &cfg,
							      have_sync);
		if (!have_sync && cfg.theta == 0)
			gain = cfg.alt_gain;
		else
			gain = cfg.gain;
		break;
	}

	fll_change |= madera_write_fll(madera, fll->base,
				       &cfg, fll->ref_src,
				       false, gain);

	/*
	 * Increase the bandwidth if we're not using a low frequency
	 * sync source.
	 */
	if (have_sync && fll->sync_freq > 100000)
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_7_OFFS,
				   MADERA_FLL1_SYNC_DFSAT_MASK, 0);
	else
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_7_OFFS,
				   MADERA_FLL1_SYNC_DFSAT_MASK,
				   MADERA_FLL1_SYNC_DFSAT);

	if (!already_enabled)
		pm_runtime_get_sync(madera->dev);

	if (have_sync)
		regmap_update_bits(madera->regmap,
				   sync_base + MADERA_FLL_SYNCHRONISER_1_OFFS,
				   MADERA_FLL1_SYNC_ENA,
				   MADERA_FLL1_SYNC_ENA);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_ENA, MADERA_FLL1_ENA);

	if (already_enabled)
		regmap_update_bits(madera->regmap,
				   fll->base + MADERA_FLL_CONTROL_1_OFFS,
				   MADERA_FLL1_FREERUN, 0);

	if (fll_change || !already_enabled)
		madera_wait_for_fll(fll, true);

	return 0;

err:
	 /* In case of error don't leave the FLL running with an old config */
	madera_disable_fll(fll);

	return ret;
}