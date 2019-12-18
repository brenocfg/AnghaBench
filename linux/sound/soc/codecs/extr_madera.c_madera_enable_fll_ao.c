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
struct reg_sequence {unsigned int def; scalar_t__ reg; } ;
struct madera_fll {unsigned int ref_src; scalar_t__ base; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MADERA_FLLAO_CONTROL_1_OFFS ; 
 scalar_t__ MADERA_FLLAO_CONTROL_6 ; 
 int /*<<< orphan*/  MADERA_FLL_AO_ENA ; 
 int /*<<< orphan*/  MADERA_FLL_AO_HOLD ; 
 unsigned int MADERA_FLL_AO_REFCLK_SRC_MASK ; 
 unsigned int MADERA_FLL_AO_REFCLK_SRC_SHIFT ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*,char*) ; 
 int madera_is_enabled_fll (struct madera_fll*,scalar_t__) ; 
 int /*<<< orphan*/  madera_wait_for_fll (struct madera_fll*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int madera_enable_fll_ao(struct madera_fll *fll,
				const struct reg_sequence *patch,
				unsigned int patch_size)
{
	struct madera *madera = fll->madera;
	int already_enabled = madera_is_enabled_fll(fll, fll->base);
	unsigned int val;
	int i;

	if (already_enabled < 0)
		return already_enabled;

	if (!already_enabled)
		pm_runtime_get_sync(madera->dev);

	madera_fll_dbg(fll, "Enabling FLL_AO, initially %s\n",
		       already_enabled ? "enabled" : "disabled");

	/* FLL_AO_HOLD must be set before configuring any registers */
	regmap_update_bits(fll->madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, MADERA_FLL_AO_HOLD);

	for (i = 0; i < patch_size; i++) {
		val = patch[i].def;

		/* modify the patch to apply fll->ref_src as input clock */
		if (patch[i].reg == MADERA_FLLAO_CONTROL_6) {
			val &= ~MADERA_FLL_AO_REFCLK_SRC_MASK;
			val |= (fll->ref_src << MADERA_FLL_AO_REFCLK_SRC_SHIFT)
				& MADERA_FLL_AO_REFCLK_SRC_MASK;
		}

		regmap_write(madera->regmap, patch[i].reg, val);
	}

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_ENA, MADERA_FLL_AO_ENA);

	/* Release the hold so that fll_ao locks to external frequency */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, 0);

	if (!already_enabled)
		madera_wait_for_fll(fll, true);

	return 0;
}