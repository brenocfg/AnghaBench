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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;
struct da7219_priv {int /*<<< orphan*/  master; struct clk** dai_clks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 size_t DA7219_DAI_BCLK_IDX ; 
 int /*<<< orphan*/  DA7219_DAI_CLK_EN_MASK ; 
 int /*<<< orphan*/  DA7219_DAI_CLK_MODE ; 
 int /*<<< orphan*/  DA7219_PC_COUNT ; 
 int /*<<< orphan*/  DA7219_PC_FREERUN_MASK ; 
 int /*<<< orphan*/  DA7219_PLL_CTRL ; 
 int DA7219_PLL_MODE_MASK ; 
 int DA7219_PLL_MODE_SRM ; 
 int /*<<< orphan*/  DA7219_PLL_SRM_STS ; 
 int DA7219_PLL_SRM_STS_SRM_LOCK ; 
 int DA7219_SRM_CHECK_RETRIES ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7219_dai_event(struct snd_soc_dapm_widget *w,
			    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	struct clk *bclk = da7219->dai_clks[DA7219_DAI_BCLK_IDX];
	u8 pll_ctrl, pll_status;
	int i = 0, ret;
	bool srm_lock = false;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (da7219->master) {
			/* Enable DAI clks for master mode */
			if (bclk) {
				ret = clk_prepare_enable(bclk);
				if (ret) {
					dev_err(component->dev,
						"Failed to enable DAI clks\n");
					return ret;
				}
			} else {
				snd_soc_component_update_bits(component,
							      DA7219_DAI_CLK_MODE,
							      DA7219_DAI_CLK_EN_MASK,
							      DA7219_DAI_CLK_EN_MASK);
			}
		}

		/* PC synchronised to DAI */
		snd_soc_component_update_bits(component, DA7219_PC_COUNT,
				    DA7219_PC_FREERUN_MASK, 0);

		/* Slave mode, if SRM not enabled no need for status checks */
		pll_ctrl = snd_soc_component_read32(component, DA7219_PLL_CTRL);
		if ((pll_ctrl & DA7219_PLL_MODE_MASK) != DA7219_PLL_MODE_SRM)
			return 0;

		/* Check SRM has locked */
		do {
			pll_status = snd_soc_component_read32(component, DA7219_PLL_SRM_STS);
			if (pll_status & DA7219_PLL_SRM_STS_SRM_LOCK) {
				srm_lock = true;
			} else {
				++i;
				msleep(50);
			}
		} while ((i < DA7219_SRM_CHECK_RETRIES) && (!srm_lock));

		if (!srm_lock)
			dev_warn(component->dev, "SRM failed to lock\n");

		return 0;
	case SND_SOC_DAPM_POST_PMD:
		/* PC free-running */
		snd_soc_component_update_bits(component, DA7219_PC_COUNT,
				    DA7219_PC_FREERUN_MASK,
				    DA7219_PC_FREERUN_MASK);

		/* Disable DAI clks if in master mode */
		if (da7219->master) {
			if (bclk)
				clk_disable_unprepare(bclk);
			else
				snd_soc_component_update_bits(component,
							      DA7219_DAI_CLK_MODE,
							      DA7219_DAI_CLK_EN_MASK,
							      0);
		}

		return 0;
	default:
		return -EINVAL;
	}
}