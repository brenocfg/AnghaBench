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
struct snd_soc_component {int dummy; } ;
struct rt5514_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  i2c_regmap; int /*<<< orphan*/  dsp_enabled; int /*<<< orphan*/  mclk; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  SND_SOC_BIAS_ON ; 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5514_i2c_patch ; 
 int /*<<< orphan*/  snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5514_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (IS_ERR(rt5514->mclk))
			break;

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) {
			clk_disable_unprepare(rt5514->mclk);
		} else {
			ret = clk_prepare_enable(rt5514->mclk);
			if (ret)
				return ret;
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			/*
			 * If the DSP is enabled in start of recording, the DSP
			 * should be disabled, and sync back to normal recording
			 * settings to make sure recording properly.
			 */
			if (rt5514->dsp_enabled) {
				rt5514->dsp_enabled = 0;
				regmap_multi_reg_write(rt5514->i2c_regmap,
					rt5514_i2c_patch,
					ARRAY_SIZE(rt5514_i2c_patch));
				regcache_mark_dirty(rt5514->regmap);
				regcache_sync(rt5514->regmap);
			}
		}
		break;

	default:
		break;
	}

	return 0;
}