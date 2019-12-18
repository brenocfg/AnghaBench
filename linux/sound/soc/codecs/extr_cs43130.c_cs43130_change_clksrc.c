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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs43130_private {int mclk_int_src; int mclk_int; int pll_bypass; int /*<<< orphan*/  regmap; int /*<<< orphan*/  pll_rdy; int /*<<< orphan*/  xtal_rdy; int /*<<< orphan*/  xtal_ibias; } ;
typedef  enum cs43130_mclk_src_sel { ____Placeholder_cs43130_mclk_src_sel } cs43130_mclk_src_sel ;

/* Variables and functions */
 int /*<<< orphan*/  CS43130_INT_MASK_1 ; 
#define  CS43130_MCLK_22M 132 
 int CS43130_MCLK_22P5 ; 
#define  CS43130_MCLK_24M 131 
 int CS43130_MCLK_24P5 ; 
 int /*<<< orphan*/  CS43130_MCLK_INT_MASK ; 
 int CS43130_MCLK_INT_SHIFT ; 
#define  CS43130_MCLK_SRC_EXT 130 
#define  CS43130_MCLK_SRC_PLL 129 
#define  CS43130_MCLK_SRC_RCO 128 
 int /*<<< orphan*/  CS43130_MCLK_SRC_SEL_MASK ; 
 int CS43130_MCLK_SRC_SEL_SHIFT ; 
 int /*<<< orphan*/  CS43130_PDN_PLL_MASK ; 
 int CS43130_PDN_PLL_SHIFT ; 
 int /*<<< orphan*/  CS43130_PDN_XTAL_MASK ; 
 int CS43130_PDN_XTAL_SHIFT ; 
 int /*<<< orphan*/  CS43130_PLL_RDY_INT_MASK ; 
 int CS43130_PLL_RDY_INT_SHIFT ; 
 int /*<<< orphan*/  CS43130_PWDN_CTL ; 
 int /*<<< orphan*/  CS43130_SYS_CLK_CTL_1 ; 
 int /*<<< orphan*/  CS43130_XTAL_RDY_INT_MASK ; 
 int CS43130_XTAL_RDY_INT_SHIFT ; 
 int /*<<< orphan*/  CS43130_XTAL_UNUSED ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct cs43130_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs43130_change_clksrc(struct snd_soc_component *component,
				 enum cs43130_mclk_src_sel src)
{
	int ret;
	struct cs43130_private *cs43130 = snd_soc_component_get_drvdata(component);
	int mclk_int_decoded;

	if (src == cs43130->mclk_int_src) {
		/* clk source has not changed */
		return 0;
	}

	switch (cs43130->mclk_int) {
	case CS43130_MCLK_22M:
		mclk_int_decoded = CS43130_MCLK_22P5;
		break;
	case CS43130_MCLK_24M:
		mclk_int_decoded = CS43130_MCLK_24P5;
		break;
	default:
		dev_err(component->dev, "Invalid MCLK INT freq: %u\n", cs43130->mclk_int);
		return -EINVAL;
	}

	switch (src) {
	case CS43130_MCLK_SRC_EXT:
		cs43130->pll_bypass = true;
		cs43130->mclk_int_src = CS43130_MCLK_SRC_EXT;
		if (cs43130->xtal_ibias == CS43130_XTAL_UNUSED) {
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK,
					   1 << CS43130_PDN_XTAL_SHIFT);
		} else {
			reinit_completion(&cs43130->xtal_rdy);
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK, 0);
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK, 0);
			ret = wait_for_completion_timeout(&cs43130->xtal_rdy,
							  msecs_to_jiffies(100));
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK,
					   1 << CS43130_XTAL_RDY_INT_SHIFT);
			if (ret == 0) {
				dev_err(component->dev, "Timeout waiting for XTAL_READY interrupt\n");
				return -ETIMEDOUT;
			}
		}

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   mclk_int_decoded << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);

		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK,
				   1 << CS43130_PDN_PLL_SHIFT);
		break;
	case CS43130_MCLK_SRC_PLL:
		cs43130->pll_bypass = false;
		cs43130->mclk_int_src = CS43130_MCLK_SRC_PLL;
		if (cs43130->xtal_ibias == CS43130_XTAL_UNUSED) {
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK,
					   1 << CS43130_PDN_XTAL_SHIFT);
		} else {
			reinit_completion(&cs43130->xtal_rdy);
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK, 0);
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK, 0);
			ret = wait_for_completion_timeout(&cs43130->xtal_rdy,
							  msecs_to_jiffies(100));
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK,
					   1 << CS43130_XTAL_RDY_INT_SHIFT);
			if (ret == 0) {
				dev_err(component->dev, "Timeout waiting for XTAL_READY interrupt\n");
				return -ETIMEDOUT;
			}
		}

		reinit_completion(&cs43130->pll_rdy);
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_PLL_RDY_INT_MASK, 0);
		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK, 0);
		ret = wait_for_completion_timeout(&cs43130->pll_rdy,
						  msecs_to_jiffies(100));
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_PLL_RDY_INT_MASK,
				   1 << CS43130_PLL_RDY_INT_SHIFT);
		if (ret == 0) {
			dev_err(component->dev, "Timeout waiting for PLL_READY interrupt\n");
			return -ETIMEDOUT;
		}

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   mclk_int_decoded << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);
		break;
	case CS43130_MCLK_SRC_RCO:
		cs43130->mclk_int_src = CS43130_MCLK_SRC_RCO;

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   CS43130_MCLK_22P5 << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);

		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_XTAL_MASK,
				   1 << CS43130_PDN_XTAL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK,
				   1 << CS43130_PDN_PLL_SHIFT);
		break;
	default:
		dev_err(component->dev, "Invalid MCLK source value\n");
		return -EINVAL;
	}

	return 0;
}