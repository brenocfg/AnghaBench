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
struct max98373_priv {int ch_size; int /*<<< orphan*/  regmap; int /*<<< orphan*/  tdm_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX98373_PCM_CLK_SETUP_BSEL_MASK ; 
 int /*<<< orphan*/  MAX98373_R2026_PCM_CLOCK_RATIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int max98373_get_bclk_sel (int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max98373_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98373_set_clock(struct snd_soc_component *component,
	struct snd_pcm_hw_params *params)
{
	struct max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	/* BCLK/LRCLK ratio calculation */
	int blr_clk_ratio = params_channels(params) * max98373->ch_size;
	int value;

	if (!max98373->tdm_mode) {
		/* BCLK configuration */
		value = max98373_get_bclk_sel(blr_clk_ratio);
		if (!value) {
			dev_err(component->dev, "format unsupported %d\n",
				params_format(params));
			return -EINVAL;
		}

		regmap_update_bits(max98373->regmap,
			MAX98373_R2026_PCM_CLOCK_RATIO,
			MAX98373_PCM_CLK_SETUP_BSEL_MASK,
			value);
	}
	return 0;
}