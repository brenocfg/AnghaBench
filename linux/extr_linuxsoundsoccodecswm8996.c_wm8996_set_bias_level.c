#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ldo_ena; } ;
struct wm8996_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8996_MICB1_MODE ; 
 int /*<<< orphan*/  WM8996_MICB2_MODE ; 
 int /*<<< orphan*/  WM8996_MICBIAS_1 ; 
 int /*<<< orphan*/  WM8996_MICBIAS_2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8996_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		/* Put the MICBIASes into regulating mode */
		snd_soc_component_update_bits(component, WM8996_MICBIAS_1,
				    WM8996_MICB1_MODE, 0);
		snd_soc_component_update_bits(component, WM8996_MICBIAS_2,
				    WM8996_MICB2_MODE, 0);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8996->supplies),
						    wm8996->supplies);
			if (ret != 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}

			if (wm8996->pdata.ldo_ena >= 0) {
				gpio_set_value_cansleep(wm8996->pdata.ldo_ena,
							1);
				msleep(5);
			}

			regcache_cache_only(wm8996->regmap, false);
			regcache_sync(wm8996->regmap);
		}

		/* Bypass the MICBIASes for lowest power */
		snd_soc_component_update_bits(component, WM8996_MICBIAS_1,
				    WM8996_MICB1_MODE, WM8996_MICB1_MODE);
		snd_soc_component_update_bits(component, WM8996_MICBIAS_2,
				    WM8996_MICB2_MODE, WM8996_MICB2_MODE);
		break;

	case SND_SOC_BIAS_OFF:
		regcache_cache_only(wm8996->regmap, true);
		if (wm8996->pdata.ldo_ena >= 0) {
			gpio_set_value_cansleep(wm8996->pdata.ldo_ena, 0);
			regcache_cache_only(wm8996->regmap, true);
		}
		regulator_bulk_disable(ARRAY_SIZE(wm8996->supplies),
				       wm8996->supplies);
		break;
	}

	return 0;
}