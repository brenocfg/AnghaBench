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
struct madera_fll {unsigned int base; struct madera* madera; } ;
struct madera {int type; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  CS47L35 128 
 unsigned int CS47L35_FLL_SYNCHRONISER_OFFS ; 
 int /*<<< orphan*/  MADERA_FLL1_ENA ; 
 int /*<<< orphan*/  MADERA_FLL1_FREERUN ; 
 int /*<<< orphan*/  MADERA_FLL1_SYNC_ENA ; 
 unsigned int MADERA_FLL_CONTROL_1_OFFS ; 
 unsigned int MADERA_FLL_SYNCHRONISER_1_OFFS ; 
 unsigned int MADERA_FLL_SYNCHRONISER_OFFS ; 
 int /*<<< orphan*/  madera_fll_dbg (struct madera_fll*,char*) ; 
 int /*<<< orphan*/  madera_wait_for_fll (struct madera_fll*,int) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void madera_disable_fll(struct madera_fll *fll)
{
	struct madera *madera = fll->madera;
	unsigned int sync_base;
	bool change;

	switch (madera->type) {
	case CS47L35:
		sync_base = fll->base + CS47L35_FLL_SYNCHRONISER_OFFS;
		break;
	default:
		sync_base = fll->base + MADERA_FLL_SYNCHRONISER_OFFS;
		break;
	}

	madera_fll_dbg(fll, "Disabling FLL\n");

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, MADERA_FLL1_FREERUN);
	regmap_update_bits_check(madera->regmap,
				 fll->base + MADERA_FLL_CONTROL_1_OFFS,
				 MADERA_FLL1_ENA, 0, &change);
	regmap_update_bits(madera->regmap,
			   sync_base + MADERA_FLL_SYNCHRONISER_1_OFFS,
			   MADERA_FLL1_SYNC_ENA, 0);
	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, 0);

	madera_wait_for_fll(fll, false);

	if (change)
		pm_runtime_put_autosuspend(madera->dev);
}