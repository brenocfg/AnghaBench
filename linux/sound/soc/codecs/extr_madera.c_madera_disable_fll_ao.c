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
struct madera_fll {scalar_t__ base; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ MADERA_FLLAO_CONTROL_1_OFFS ; 
 scalar_t__ MADERA_FLLAO_CONTROL_2_OFFS ; 
 int /*<<< orphan*/  MADERA_FLL_AO_CTRL_UPD_MASK ; 
 int /*<<< orphan*/  MADERA_FLL_AO_ENA ; 
 int /*<<< orphan*/  MADERA_FLL_AO_HOLD ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*) ; 
 int /*<<< orphan*/  madera_wait_for_fll (struct madera_fll*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int madera_disable_fll_ao(struct madera_fll *fll)
{
	struct madera *madera = fll->madera;
	bool change;

	madera_fll_dbg(fll, "Disabling FLL_AO\n");

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
			   MADERA_FLL_AO_HOLD, MADERA_FLL_AO_HOLD);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLLAO_CONTROL_1_OFFS,
				 MADERA_FLL_AO_ENA, 0, &change);

	madera_wait_for_fll(fll, false);

	/*
	 * ctrl_up gates the writes to all fll_ao register, setting it to 0
	 * here ensures that after a runtime suspend/resume cycle when one
	 * enables the fllao then ctrl_up is the last bit that is configured
	 * by the fllao enable code rather than the cache sync operation which
	 * would have updated it much earlier before writing out all fllao
	 * registers
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLLAO_CONTROL_2_OFFS,
			   MADERA_FLL_AO_CTRL_UPD_MASK, 0);

	if (change)
		pm_runtime_put_autosuspend(madera->dev);

	return 0;
}