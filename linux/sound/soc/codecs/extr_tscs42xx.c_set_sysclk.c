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
struct tscs42xx {int sysclk_src_id; int /*<<< orphan*/  sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int RV_PLLREFSEL_PLL1_REF_SEL_MCLK2 ; 
 int RV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1 ; 
 int RV_PLLREFSEL_PLL2_REF_SEL_MCLK2 ; 
 int RV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1 ; 
 int /*<<< orphan*/  R_PLLREFSEL ; 
#define  TSCS42XX_PLL_SRC_MCLK1 130 
#define  TSCS42XX_PLL_SRC_MCLK2 129 
#define  TSCS42XX_PLL_SRC_XTAL 128 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int set_pll_ctl_from_input_freq (struct snd_soc_component*,unsigned long) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_sysclk(struct snd_soc_component *component)
{
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	unsigned long freq;
	int ret;

	switch (tscs42xx->sysclk_src_id) {
	case TSCS42XX_PLL_SRC_XTAL:
	case TSCS42XX_PLL_SRC_MCLK1:
		ret = snd_soc_component_write(component, R_PLLREFSEL,
				RV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1 |
				RV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1);
		if (ret < 0) {
			dev_err(component->dev,
				"Failed to set pll reference input (%d)\n",
				ret);
			return ret;
		}
		break;
	case TSCS42XX_PLL_SRC_MCLK2:
		ret = snd_soc_component_write(component, R_PLLREFSEL,
				RV_PLLREFSEL_PLL1_REF_SEL_MCLK2 |
				RV_PLLREFSEL_PLL2_REF_SEL_MCLK2);
		if (ret < 0) {
			dev_err(component->dev,
				"Failed to set PLL reference (%d)\n", ret);
			return ret;
		}
		break;
	default:
		dev_err(component->dev, "pll src is unsupported\n");
		return -EINVAL;
	}

	freq = clk_get_rate(tscs42xx->sysclk);
	ret = set_pll_ctl_from_input_freq(component, freq);
	if (ret < 0) {
		dev_err(component->dev,
			"Failed to setup PLL input freq (%d)\n", ret);
		return ret;
	}

	return 0;
}