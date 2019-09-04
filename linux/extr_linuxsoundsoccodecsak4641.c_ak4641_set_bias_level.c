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
struct snd_soc_component {TYPE_1__* dev; } ;
struct ak4641_priv {int /*<<< orphan*/  regmap; } ;
struct ak4641_platform_data {int /*<<< orphan*/  gpio_power; int /*<<< orphan*/  gpio_npdn; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;
struct TYPE_2__ {struct ak4641_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4641_DAC ; 
 int /*<<< orphan*/  AK4641_PM1 ; 
 int /*<<< orphan*/  AK4641_PM2 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct ak4641_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak4641_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct ak4641_priv *ak4641 = snd_soc_component_get_drvdata(component);
	struct ak4641_platform_data *pdata = component->dev->platform_data;
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* unmute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0);
		break;
	case SND_SOC_BIAS_PREPARE:
		/* mute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0x20);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			if (pdata && gpio_is_valid(pdata->gpio_power))
				gpio_set_value(pdata->gpio_power, 1);
			mdelay(1);
			if (pdata && gpio_is_valid(pdata->gpio_npdn))
				gpio_set_value(pdata->gpio_npdn, 1);
			mdelay(1);

			ret = regcache_sync(ak4641->regmap);
			if (ret) {
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				return ret;
			}
		}
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0x80);
		snd_soc_component_update_bits(component, AK4641_PM2, 0x80, 0);
		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0);
		if (pdata && gpio_is_valid(pdata->gpio_npdn))
			gpio_set_value(pdata->gpio_npdn, 0);
		if (pdata && gpio_is_valid(pdata->gpio_power))
			gpio_set_value(pdata->gpio_power, 0);
		regcache_mark_dirty(ak4641->regmap);
		break;
	}
	return 0;
}