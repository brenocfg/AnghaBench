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
struct arizona_fll_cfg {int theta; int lambda; int fratio; int refdiv; int gain; int outdiv; int n; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARIZONA_FLL1_CLK_REF_DIV_MASK ; 
 int ARIZONA_FLL1_CLK_REF_DIV_SHIFT ; 
 int ARIZONA_FLL1_CLK_REF_SRC_MASK ; 
 int ARIZONA_FLL1_CLK_REF_SRC_SHIFT ; 
 int ARIZONA_FLL1_CTRL_UPD ; 
 int ARIZONA_FLL1_FRATIO_MASK ; 
 int ARIZONA_FLL1_FRATIO_SHIFT ; 
 int /*<<< orphan*/  ARIZONA_FLL1_GAIN_MASK ; 
 int ARIZONA_FLL1_GAIN_SHIFT ; 
 int ARIZONA_FLL1_LAMBDA_MASK ; 
 int ARIZONA_FLL1_N_MASK ; 
 int /*<<< orphan*/  ARIZONA_FLL1_OUTDIV_MASK ; 
 int ARIZONA_FLL1_OUTDIV_SHIFT ; 
 int ARIZONA_FLL1_THETA_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits_async (int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static void arizona_apply_fll(struct arizona *arizona, unsigned int base,
			      struct arizona_fll_cfg *cfg, int source,
			      bool sync)
{
	regmap_update_bits_async(arizona->regmap, base + 3,
				 ARIZONA_FLL1_THETA_MASK, cfg->theta);
	regmap_update_bits_async(arizona->regmap, base + 4,
				 ARIZONA_FLL1_LAMBDA_MASK, cfg->lambda);
	regmap_update_bits_async(arizona->regmap, base + 5,
				 ARIZONA_FLL1_FRATIO_MASK,
				 cfg->fratio << ARIZONA_FLL1_FRATIO_SHIFT);
	regmap_update_bits_async(arizona->regmap, base + 6,
				 ARIZONA_FLL1_CLK_REF_DIV_MASK |
				 ARIZONA_FLL1_CLK_REF_SRC_MASK,
				 cfg->refdiv << ARIZONA_FLL1_CLK_REF_DIV_SHIFT |
				 source << ARIZONA_FLL1_CLK_REF_SRC_SHIFT);

	if (sync) {
		regmap_update_bits(arizona->regmap, base + 0x7,
				   ARIZONA_FLL1_GAIN_MASK,
				   cfg->gain << ARIZONA_FLL1_GAIN_SHIFT);
	} else {
		regmap_update_bits(arizona->regmap, base + 0x5,
				   ARIZONA_FLL1_OUTDIV_MASK,
				   cfg->outdiv << ARIZONA_FLL1_OUTDIV_SHIFT);
		regmap_update_bits(arizona->regmap, base + 0x9,
				   ARIZONA_FLL1_GAIN_MASK,
				   cfg->gain << ARIZONA_FLL1_GAIN_SHIFT);
	}

	regmap_update_bits_async(arizona->regmap, base + 2,
				 ARIZONA_FLL1_CTRL_UPD | ARIZONA_FLL1_N_MASK,
				 ARIZONA_FLL1_CTRL_UPD | cfg->n);
}