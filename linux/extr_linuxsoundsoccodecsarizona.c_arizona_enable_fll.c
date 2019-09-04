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
struct arizona_fll_cfg {int lambda; int theta; } ;
struct arizona_fll {int ref_freq; int sync_freq; int id; scalar_t__ base; int /*<<< orphan*/  sync_src; int /*<<< orphan*/  ref_src; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARIZONA_FLL1_CLOCK_OK_STS ; 
 int /*<<< orphan*/  ARIZONA_FLL1_ENA ; 
 int /*<<< orphan*/  ARIZONA_FLL1_FREERUN ; 
 int /*<<< orphan*/  ARIZONA_FLL1_GAIN_MASK ; 
 int /*<<< orphan*/  ARIZONA_FLL1_SYNC_BW ; 
 int /*<<< orphan*/  ARIZONA_FLL1_SYNC_ENA ; 
 int /*<<< orphan*/  ARIZONA_INTERRUPT_RAW_STATUS_5 ; 
 int EINVAL ; 
 int /*<<< orphan*/  arizona_apply_fll (struct arizona*,scalar_t__,struct arizona_fll_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arizona_calc_fll (struct arizona_fll*,struct arizona_fll_cfg*,int,int) ; 
 int /*<<< orphan*/  arizona_fll_dbg (struct arizona_fll*,char*,...) ; 
 int /*<<< orphan*/  arizona_fll_err (struct arizona_fll*,char*) ; 
 int /*<<< orphan*/  arizona_fll_warn (struct arizona_fll*,char*) ; 
 int arizona_is_enabled_fll (struct arizona_fll*,scalar_t__) ; 
 int /*<<< orphan*/  arizona_set_fll_clks (struct arizona_fll*,scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int arizona_enable_fll(struct arizona_fll *fll)
{
	struct arizona *arizona = fll->arizona;
	bool use_sync = false;
	int already_enabled = arizona_is_enabled_fll(fll, fll->base);
	int sync_enabled = arizona_is_enabled_fll(fll, fll->base + 0x10);
	struct arizona_fll_cfg cfg;
	int i;
	unsigned int val;

	if (already_enabled < 0)
		return already_enabled;
	if (sync_enabled < 0)
		return sync_enabled;

	if (already_enabled) {
		/* Facilitate smooth refclk across the transition */
		regmap_update_bits(fll->arizona->regmap, fll->base + 1,
				   ARIZONA_FLL1_FREERUN, ARIZONA_FLL1_FREERUN);
		udelay(32);
		regmap_update_bits_async(fll->arizona->regmap, fll->base + 0x9,
					 ARIZONA_FLL1_GAIN_MASK, 0);

		if (arizona_is_enabled_fll(fll, fll->base + 0x10) > 0)
			arizona_set_fll_clks(fll, fll->base + 0x10, false);
		arizona_set_fll_clks(fll, fll->base, false);
	}

	/*
	 * If we have both REFCLK and SYNCCLK then enable both,
	 * otherwise apply the SYNCCLK settings to REFCLK.
	 */
	if (fll->ref_src >= 0 && fll->ref_freq &&
	    fll->ref_src != fll->sync_src) {
		arizona_calc_fll(fll, &cfg, fll->ref_freq, false);

		/* Ref path hardcodes lambda to 65536 when sync is on */
		if (fll->sync_src >= 0 && cfg.lambda)
			cfg.theta = (cfg.theta * (1 << 16)) / cfg.lambda;

		arizona_apply_fll(arizona, fll->base, &cfg, fll->ref_src,
				  false);
		if (fll->sync_src >= 0) {
			arizona_calc_fll(fll, &cfg, fll->sync_freq, true);

			arizona_apply_fll(arizona, fll->base + 0x10, &cfg,
					  fll->sync_src, true);
			use_sync = true;
		}
	} else if (fll->sync_src >= 0) {
		arizona_calc_fll(fll, &cfg, fll->sync_freq, false);

		arizona_apply_fll(arizona, fll->base, &cfg,
				  fll->sync_src, false);

		regmap_update_bits_async(arizona->regmap, fll->base + 0x11,
					 ARIZONA_FLL1_SYNC_ENA, 0);
	} else {
		arizona_fll_err(fll, "No clocks provided\n");
		return -EINVAL;
	}

	if (already_enabled && !!sync_enabled != use_sync)
		arizona_fll_warn(fll, "Synchroniser changed on active FLL\n");

	/*
	 * Increase the bandwidth if we're not using a low frequency
	 * sync source.
	 */
	if (use_sync && fll->sync_freq > 100000)
		regmap_update_bits_async(arizona->regmap, fll->base + 0x17,
					 ARIZONA_FLL1_SYNC_BW, 0);
	else
		regmap_update_bits_async(arizona->regmap, fll->base + 0x17,
					 ARIZONA_FLL1_SYNC_BW,
					 ARIZONA_FLL1_SYNC_BW);

	if (!already_enabled)
		pm_runtime_get_sync(arizona->dev);

	if (use_sync) {
		arizona_set_fll_clks(fll, fll->base + 0x10, true);
		regmap_update_bits_async(arizona->regmap, fll->base + 0x11,
					 ARIZONA_FLL1_SYNC_ENA,
					 ARIZONA_FLL1_SYNC_ENA);
	}
	arizona_set_fll_clks(fll, fll->base, true);
	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_ENA, ARIZONA_FLL1_ENA);

	if (already_enabled)
		regmap_update_bits_async(arizona->regmap, fll->base + 1,
					 ARIZONA_FLL1_FREERUN, 0);

	arizona_fll_dbg(fll, "Waiting for FLL lock...\n");
	val = 0;
	for (i = 0; i < 15; i++) {
		if (i < 5)
			usleep_range(200, 400);
		else
			msleep(20);

		regmap_read(arizona->regmap,
			    ARIZONA_INTERRUPT_RAW_STATUS_5,
			    &val);
		if (val & (ARIZONA_FLL1_CLOCK_OK_STS << (fll->id - 1)))
			break;
	}
	if (i == 15)
		arizona_fll_warn(fll, "Timed out waiting for lock\n");
	else
		arizona_fll_dbg(fll, "FLL locked (%d polls)\n", i);

	return 0;
}