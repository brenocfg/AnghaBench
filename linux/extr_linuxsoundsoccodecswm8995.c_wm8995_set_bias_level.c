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
struct wm8995_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8995_BG_ENA ; 
 int /*<<< orphan*/  WM8995_BG_ENA_MASK ; 
 int /*<<< orphan*/  WM8995_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8995_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8995_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8995_priv *wm8995;
	int ret;

	wm8995 = snd_soc_component_get_drvdata(component);
	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8995->supplies),
						    wm8995->supplies);
			if (ret)
				return ret;

			ret = regcache_sync(wm8995->regmap);
			if (ret) {
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				return ret;
			}

			snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
					    WM8995_BG_ENA_MASK, WM8995_BG_ENA);
		}
		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_BG_ENA_MASK, 0);
		regulator_bulk_disable(ARRAY_SIZE(wm8995->supplies),
				       wm8995->supplies);
		break;
	}

	return 0;
}