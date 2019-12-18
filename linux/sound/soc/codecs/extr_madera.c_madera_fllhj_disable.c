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
 int /*<<< orphan*/  MADERA_FLL1_CTRL_UPD_MASK ; 
 int /*<<< orphan*/  MADERA_FLL1_ENA_MASK ; 
 int /*<<< orphan*/  MADERA_FLL1_HOLD_MASK ; 
 int /*<<< orphan*/  MADERA_FLL1_LOCKDET_MASK ; 
 scalar_t__ MADERA_FLL_CONTROL_11_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_1_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_2_OFFS ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*) ; 
 int /*<<< orphan*/  madera_wait_for_fll (struct madera_fll*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int madera_fllhj_disable(struct madera_fll *fll)
{
	struct madera *madera = fll->madera;
	bool change;

	madera_fll_dbg(fll, "Disabling FLL\n");

	/* Disable lockdet, but don't set ctrl_upd update but.  This allows the
	 * lock status bit to clear as normal, but should the FLL be enabled
	 * again due to a control clock being required, the lock won't re-assert
	 * as the FLL config registers are automatically applied when the FLL
	 * enables.
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_11_OFFS,
			   MADERA_FLL1_LOCKDET_MASK, 0);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_HOLD_MASK, MADERA_FLL1_HOLD_MASK);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLL_CONTROL_1_OFFS,
				 MADERA_FLL1_ENA_MASK, 0, &change);

	madera_wait_for_fll(fll, false);

	/* ctrl_up gates the writes to all the fll's registers, setting it to 0
	 * here ensures that after a runtime suspend/resume cycle when one
	 * enables the fll then ctrl_up is the last bit that is configured
	 * by the fll enable code rather than the cache sync operation which
	 * would have updated it much earlier before writing out all fll
	 * registers
	 */
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_2_OFFS,
			   MADERA_FLL1_CTRL_UPD_MASK, 0);

	if (change)
		pm_runtime_put_autosuspend(madera->dev);

	return 0;
}