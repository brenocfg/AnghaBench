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
struct regmap {int dummy; } ;
struct nau8824_fll {int mclk_src; int ratio; int fll_int; int clk_ref_div; scalar_t__ fll_frac; } ;

/* Variables and functions */
 int NAU8824_CLK_MCLK_SRC_MASK ; 
 int NAU8824_CLK_SRC_MASK ; 
 int NAU8824_CLK_SRC_MCLK ; 
 int NAU8824_DCO_EN ; 
 int NAU8824_FLL_CLK_SW_MASK ; 
 int NAU8824_FLL_CLK_SW_REF ; 
 int NAU8824_FLL_FTR_SW_ACCU ; 
 int NAU8824_FLL_FTR_SW_FILTER ; 
 int NAU8824_FLL_FTR_SW_MASK ; 
 int NAU8824_FLL_INTEGER_MASK ; 
 int NAU8824_FLL_LOOP_FTR_EN ; 
 int NAU8824_FLL_PDB_DAC_EN ; 
 int NAU8824_FLL_RATIO_MASK ; 
 int NAU8824_FLL_REF_DIV_MASK ; 
 int NAU8824_FLL_REF_DIV_SFT ; 
 int /*<<< orphan*/  NAU8824_REG_CLK_DIVIDER ; 
 int /*<<< orphan*/  NAU8824_REG_FLL1 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL2 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL3 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL4 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL5 ; 
 int /*<<< orphan*/  NAU8824_REG_FLL6 ; 
 int NAU8824_SDM_EN ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nau8824_fll_apply(struct regmap *regmap,
	struct nau8824_fll *fll_param)
{
	regmap_update_bits(regmap, NAU8824_REG_CLK_DIVIDER,
		NAU8824_CLK_SRC_MASK | NAU8824_CLK_MCLK_SRC_MASK,
		NAU8824_CLK_SRC_MCLK | fll_param->mclk_src);
	regmap_update_bits(regmap, NAU8824_REG_FLL1,
		NAU8824_FLL_RATIO_MASK, fll_param->ratio);
	/* FLL 16-bit fractional input */
	regmap_write(regmap, NAU8824_REG_FLL2, fll_param->fll_frac);
	/* FLL 10-bit integer input */
	regmap_update_bits(regmap, NAU8824_REG_FLL3,
		NAU8824_FLL_INTEGER_MASK, fll_param->fll_int);
	/* FLL pre-scaler */
	regmap_update_bits(regmap, NAU8824_REG_FLL4,
		NAU8824_FLL_REF_DIV_MASK,
		fll_param->clk_ref_div << NAU8824_FLL_REF_DIV_SFT);
	/* select divided VCO input */
	regmap_update_bits(regmap, NAU8824_REG_FLL5,
		NAU8824_FLL_CLK_SW_MASK, NAU8824_FLL_CLK_SW_REF);
	/* Disable free-running mode */
	regmap_update_bits(regmap,
		NAU8824_REG_FLL6, NAU8824_DCO_EN, 0);
	if (fll_param->fll_frac) {
		regmap_update_bits(regmap, NAU8824_REG_FLL5,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_MASK,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_FILTER);
		regmap_update_bits(regmap, NAU8824_REG_FLL6,
			NAU8824_SDM_EN, NAU8824_SDM_EN);
	} else {
		regmap_update_bits(regmap, NAU8824_REG_FLL5,
			NAU8824_FLL_PDB_DAC_EN | NAU8824_FLL_LOOP_FTR_EN |
			NAU8824_FLL_FTR_SW_MASK, NAU8824_FLL_FTR_SW_ACCU);
		regmap_update_bits(regmap,
			NAU8824_REG_FLL6, NAU8824_SDM_EN, 0);
	}
}