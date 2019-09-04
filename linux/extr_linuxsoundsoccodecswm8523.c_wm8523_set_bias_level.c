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
struct wm8523_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8523_PSCTRL1 ; 
 int /*<<< orphan*/  WM8523_SYS_ENA_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8523_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8523_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* Full power on */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 3);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8523->supplies),
						    wm8523->supplies);
			if (ret != 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}

			/* Sync back default/cached values */
			regcache_sync(wm8523->regmap);

			/* Initial power up */
			snd_soc_component_update_bits(component, WM8523_PSCTRL1,
					    WM8523_SYS_ENA_MASK, 1);

			msleep(100);
		}

		/* Power up to mute */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 2);

		break;

	case SND_SOC_BIAS_OFF:
		/* The chip runs through the power down sequence for us. */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 0);
		msleep(100);

		regulator_bulk_disable(ARRAY_SIZE(wm8523->supplies),
				       wm8523->supplies);
		break;
	}
	return 0;
}