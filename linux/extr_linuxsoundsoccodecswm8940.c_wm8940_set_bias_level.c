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
typedef  int u16 ;
struct wm8940_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8940_OUTPUTCTL ; 
 int /*<<< orphan*/  WM8940_POWER1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8940_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8940_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8940_priv *wm8940 = snd_soc_component_get_drvdata(component);
	u16 val;
	u16 pwr_reg = snd_soc_component_read32(component, WM8940_POWER1) & 0x1F0;
	int ret = 0;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		/* Enable thermal shutdown */
		val = snd_soc_component_read32(component, WM8940_OUTPUTCTL);
		ret = snd_soc_component_write(component, WM8940_OUTPUTCTL, val | 0x2);
		if (ret)
			break;
		/* set vmid to 75k */
		ret = snd_soc_component_write(component, WM8940_POWER1, pwr_reg | 0x1);
		break;
	case SND_SOC_BIAS_PREPARE:
		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		ret = snd_soc_component_write(component, WM8940_POWER1, pwr_reg | 0x1);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regcache_sync(wm8940->regmap);
			if (ret < 0) {
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				return ret;
			}
		}

		/* ensure bufioen and biasen */
		pwr_reg |= (1 << 2) | (1 << 3);
		/* set vmid to 300k for standby */
		ret = snd_soc_component_write(component, WM8940_POWER1, pwr_reg | 0x2);
		break;
	case SND_SOC_BIAS_OFF:
		ret = snd_soc_component_write(component, WM8940_POWER1, pwr_reg);
		break;
	}

	return ret;
}