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
struct madera_fll_cfg {int theta; int lambda; int fratio; int refdiv; int n; } ;
struct madera {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int MADERA_FLL1_CTRL_UPD ; 
 int MADERA_FLL1_FRATIO_MASK ; 
 int MADERA_FLL1_FRATIO_SHIFT ; 
 int MADERA_FLL1_GAIN_MASK ; 
 int MADERA_FLL1_GAIN_SHIFT ; 
 int MADERA_FLL1_LAMBDA_MASK ; 
 int MADERA_FLL1_N_MASK ; 
 int MADERA_FLL1_REFCLK_DIV_MASK ; 
 int MADERA_FLL1_REFCLK_DIV_SHIFT ; 
 int MADERA_FLL1_REFCLK_SRC_MASK ; 
 int MADERA_FLL1_REFCLK_SRC_SHIFT ; 
 int MADERA_FLL1_THETA_MASK ; 
 scalar_t__ MADERA_FLL_CONTROL_2_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_3_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_4_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_5_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_6_OFFS ; 
 scalar_t__ MADERA_FLL_CONTROL_7_OFFS ; 
 scalar_t__ MADERA_FLL_SYNCHRONISER_7_OFFS ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,scalar_t__,int,int,int*) ; 

__attribute__((used)) static bool madera_write_fll(struct madera *madera, unsigned int base,
			     struct madera_fll_cfg *cfg, int source,
			     bool sync, int gain)
{
	bool change, fll_change;

	fll_change = false;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_3_OFFS,
				 MADERA_FLL1_THETA_MASK,
				 cfg->theta, &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_4_OFFS,
				 MADERA_FLL1_LAMBDA_MASK,
				 cfg->lambda, &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_5_OFFS,
				 MADERA_FLL1_FRATIO_MASK,
				 cfg->fratio << MADERA_FLL1_FRATIO_SHIFT,
				 &change);
	fll_change |= change;
	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_6_OFFS,
				 MADERA_FLL1_REFCLK_DIV_MASK |
				 MADERA_FLL1_REFCLK_SRC_MASK,
				 cfg->refdiv << MADERA_FLL1_REFCLK_DIV_SHIFT |
				 source << MADERA_FLL1_REFCLK_SRC_SHIFT,
				 &change);
	fll_change |= change;

	if (sync) {
		regmap_update_bits_check(madera->regmap,
					 base + MADERA_FLL_SYNCHRONISER_7_OFFS,
					 MADERA_FLL1_GAIN_MASK,
					 gain << MADERA_FLL1_GAIN_SHIFT,
					 &change);
		fll_change |= change;
	} else {
		regmap_update_bits_check(madera->regmap,
					 base + MADERA_FLL_CONTROL_7_OFFS,
					 MADERA_FLL1_GAIN_MASK,
					 gain << MADERA_FLL1_GAIN_SHIFT,
					 &change);
		fll_change |= change;
	}

	regmap_update_bits_check(madera->regmap,
				 base + MADERA_FLL_CONTROL_2_OFFS,
				 MADERA_FLL1_CTRL_UPD | MADERA_FLL1_N_MASK,
				 MADERA_FLL1_CTRL_UPD | cfg->n, &change);
	fll_change |= change;

	return fll_change;
}