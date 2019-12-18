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
struct snd_pcm_hw_params {int dummy; } ;
struct max98927_priv {int ch_size; scalar_t__ sysclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  tdm_mode; scalar_t__ master; struct snd_soc_component* component; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX98927_PCM_CLK_SETUP_BSEL_MASK ; 
 int /*<<< orphan*/  MAX98927_PCM_MASTER_MODE_MCLK_MASK ; 
 int MAX98927_PCM_MASTER_MODE_MCLK_RATE_SHIFT ; 
 int /*<<< orphan*/  MAX98927_R0021_PCM_MASTER_MODE ; 
 int /*<<< orphan*/  MAX98927_R0022_PCM_CLK_SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int max98927_get_bclk_sel (int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 scalar_t__* rate_table ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max98927_set_clock(struct max98927_priv *max98927,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_component *component = max98927->component;
	/* BCLK/LRCLK ratio calculation */
	int blr_clk_ratio = params_channels(params) * max98927->ch_size;
	int value;

	if (max98927->master) {
		int i;
		/* match rate to closest value */
		for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
			if (rate_table[i] >= max98927->sysclk)
				break;
		}
		if (i == ARRAY_SIZE(rate_table)) {
			dev_err(component->dev, "failed to find proper clock rate.\n");
			return -EINVAL;
		}
		regmap_update_bits(max98927->regmap,
			MAX98927_R0021_PCM_MASTER_MODE,
			MAX98927_PCM_MASTER_MODE_MCLK_MASK,
			i << MAX98927_PCM_MASTER_MODE_MCLK_RATE_SHIFT);
	}

	if (!max98927->tdm_mode) {
		/* BCLK configuration */
		value = max98927_get_bclk_sel(blr_clk_ratio);
		if (!value) {
			dev_err(component->dev, "format unsupported %d\n",
				params_format(params));
			return -EINVAL;
		}

		regmap_update_bits(max98927->regmap,
			MAX98927_R0022_PCM_CLK_SETUP,
			MAX98927_PCM_CLK_SETUP_BSEL_MASK,
			value);
	}
	return 0;
}