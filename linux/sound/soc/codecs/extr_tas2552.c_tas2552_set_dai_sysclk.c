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
typedef  int u8 ;
struct tas2552_data {int pll_clk_id; unsigned int pll_clkin; int pdm_clk_id; unsigned int pdm_clk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int TAS2552_CFG_1 ; 
 int TAS2552_PDM_CFG ; 
#define  TAS2552_PDM_CLK_BCLK 135 
#define  TAS2552_PDM_CLK_IVCLKIN 134 
#define  TAS2552_PDM_CLK_MCLK 133 
#define  TAS2552_PDM_CLK_PLL 132 
 int TAS2552_PDM_CLK_SEL_MASK ; 
#define  TAS2552_PLL_CLKIN_1_8_FIXED 131 
#define  TAS2552_PLL_CLKIN_BCLK 130 
#define  TAS2552_PLL_CLKIN_IVCLKIN 129 
#define  TAS2552_PLL_CLKIN_MCLK 128 
 int TAS2552_PLL_SRC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tas2552_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int tas2552_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				  unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct tas2552_data *tas2552 = dev_get_drvdata(component->dev);
	u8 reg, mask, val;

	switch (clk_id) {
	case TAS2552_PLL_CLKIN_MCLK:
	case TAS2552_PLL_CLKIN_IVCLKIN:
		if (freq < 512000 || freq > 24576000) {
			/* out of range PLL_CLKIN, fall back to use BCLK */
			dev_warn(component->dev, "Out of range PLL_CLKIN: %u\n",
				 freq);
			clk_id = TAS2552_PLL_CLKIN_BCLK;
			freq = 0;
		}
		/* fall through */
	case TAS2552_PLL_CLKIN_BCLK:
	case TAS2552_PLL_CLKIN_1_8_FIXED:
		mask = TAS2552_PLL_SRC_MASK;
		val = (clk_id << 3) & mask; /* bit 4:5 in the register */
		reg = TAS2552_CFG_1;
		tas2552->pll_clk_id = clk_id;
		tas2552->pll_clkin = freq;
		break;
	case TAS2552_PDM_CLK_PLL:
	case TAS2552_PDM_CLK_IVCLKIN:
	case TAS2552_PDM_CLK_BCLK:
	case TAS2552_PDM_CLK_MCLK:
		mask = TAS2552_PDM_CLK_SEL_MASK;
		val = (clk_id >> 1) & mask; /* bit 0:1 in the register */
		reg = TAS2552_PDM_CFG;
		tas2552->pdm_clk_id = clk_id;
		tas2552->pdm_clk = freq;
		break;
	default:
		dev_err(component->dev, "Invalid clk id: %d\n", clk_id);
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, reg, mask, val);

	return 0;
}