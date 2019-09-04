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
struct arizona_fll {scalar_t__ base; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_FLL1_ENA ; 
 int /*<<< orphan*/  ARIZONA_FLL1_FREERUN ; 
 int /*<<< orphan*/  ARIZONA_FLL1_SYNC_ENA ; 
 int /*<<< orphan*/  arizona_set_fll_clks (struct arizona_fll*,scalar_t__,int) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void arizona_disable_fll(struct arizona_fll *fll)
{
	struct arizona *arizona = fll->arizona;
	bool ref_change, sync_change;

	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_FREERUN, ARIZONA_FLL1_FREERUN);
	regmap_update_bits_check(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_ENA, 0, &ref_change);
	regmap_update_bits_check(arizona->regmap, fll->base + 0x11,
				 ARIZONA_FLL1_SYNC_ENA, 0, &sync_change);
	regmap_update_bits_async(arizona->regmap, fll->base + 1,
				 ARIZONA_FLL1_FREERUN, 0);

	if (sync_change)
		arizona_set_fll_clks(fll, fll->base + 0x10, false);

	if (ref_change) {
		arizona_set_fll_clks(fll, fll->base, false);
		pm_runtime_put_autosuspend(arizona->dev);
	}
}