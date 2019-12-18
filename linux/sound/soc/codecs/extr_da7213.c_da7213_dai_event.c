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
struct da7213_priv {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7213_DAI_CLK_EN_MASK ; 
 int /*<<< orphan*/  DA7213_DAI_CLK_MODE ; 
 int /*<<< orphan*/  DA7213_PC_COUNT ; 
 int /*<<< orphan*/  DA7213_PC_FREERUN_MASK ; 
 int DA7213_PLL_32K_MODE ; 
 int /*<<< orphan*/  DA7213_PLL_CTRL ; 
 int DA7213_PLL_SRM_EN ; 
 int /*<<< orphan*/  DA7213_PLL_STATUS ; 
 int DA7213_SRM_CHECK_RETRIES ; 
 int DA7219_PLL_SRM_LOCK ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct da7213_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7213_dai_event(struct snd_soc_dapm_widget *w,
			    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct da7213_priv *da7213 = snd_soc_component_get_drvdata(component);
	u8 pll_ctrl, pll_status;
	int i = 0;
	bool srm_lock = false;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Enable DAI clks for master mode */
		if (da7213->master)
			snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
					    DA7213_DAI_CLK_EN_MASK,
					    DA7213_DAI_CLK_EN_MASK);

		/* PC synchronised to DAI */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FREERUN_MASK, 0);

		/* If SRM not enabled then nothing more to do */
		pll_ctrl = snd_soc_component_read32(component, DA7213_PLL_CTRL);
		if (!(pll_ctrl & DA7213_PLL_SRM_EN))
			return 0;

		/* Assist 32KHz mode PLL lock */
		if (pll_ctrl & DA7213_PLL_32K_MODE) {
			snd_soc_component_write(component, 0xF0, 0x8B);
			snd_soc_component_write(component, 0xF2, 0x03);
			snd_soc_component_write(component, 0xF0, 0x00);
		}

		/* Check SRM has locked */
		do {
			pll_status = snd_soc_component_read32(component, DA7213_PLL_STATUS);
			if (pll_status & DA7219_PLL_SRM_LOCK) {
				srm_lock = true;
			} else {
				++i;
				msleep(50);
			}
		} while ((i < DA7213_SRM_CHECK_RETRIES) && (!srm_lock));

		if (!srm_lock)
			dev_warn(component->dev, "SRM failed to lock\n");

		return 0;
	case SND_SOC_DAPM_POST_PMD:
		/* Revert 32KHz PLL lock udpates if applied previously */
		pll_ctrl = snd_soc_component_read32(component, DA7213_PLL_CTRL);
		if (pll_ctrl & DA7213_PLL_32K_MODE) {
			snd_soc_component_write(component, 0xF0, 0x8B);
			snd_soc_component_write(component, 0xF2, 0x01);
			snd_soc_component_write(component, 0xF0, 0x00);
		}

		/* PC free-running */
		snd_soc_component_update_bits(component, DA7213_PC_COUNT,
				    DA7213_PC_FREERUN_MASK,
				    DA7213_PC_FREERUN_MASK);

		/* Disable DAI clks if in master mode */
		if (da7213->master)
			snd_soc_component_update_bits(component, DA7213_DAI_CLK_MODE,
					    DA7213_DAI_CLK_EN_MASK, 0);
		return 0;
	default:
		return -EINVAL;
	}
}