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
struct wm8990_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8990_ANTIPOP1 ; 
 int /*<<< orphan*/  WM8990_ANTIPOP2 ; 
 int WM8990_BUFDCOPEN ; 
 int WM8990_BUFIOEN ; 
 int /*<<< orphan*/  WM8990_DAC_CTRL ; 
 int WM8990_DAC_MUTE ; 
 int WM8990_DIS_LLINE ; 
 int WM8990_DIS_LOUT ; 
 int WM8990_DIS_OUT3 ; 
 int WM8990_DIS_OUT4 ; 
 int WM8990_DIS_RLINE ; 
 int WM8990_DIS_ROUT ; 
 int /*<<< orphan*/  WM8990_EXT_ACCESS_ENA ; 
 int /*<<< orphan*/  WM8990_EXT_CTL1 ; 
 int WM8990_POBCTRL ; 
 int /*<<< orphan*/  WM8990_POWER_MANAGEMENT_1 ; 
 int WM8990_SOFTST ; 
 int WM8990_VMIDTOG ; 
 int WM8990_VMID_MODE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8990_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8990_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct wm8990_priv *wm8990 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID=2*50k */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x2);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regcache_sync(wm8990->regmap);
			if (ret < 0) {
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				return ret;
			}

			/* Enable all output discharge bits */
			snd_soc_component_write(component, WM8990_ANTIPOP1, WM8990_DIS_LLINE |
				WM8990_DIS_RLINE | WM8990_DIS_OUT3 |
				WM8990_DIS_OUT4 | WM8990_DIS_LOUT |
				WM8990_DIS_ROUT);

			/* Enable POBCTRL, SOFT_ST, VMIDTOG and BUFDCOPEN */
			snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL |
				     WM8990_VMIDTOG);

			/* Delay to allow output caps to discharge */
			msleep(300);

			/* Disable VMIDTOG */
			snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL);

			/* disable all output discharge bits */
			snd_soc_component_write(component, WM8990_ANTIPOP1, 0);

			/* Enable outputs */
			snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x1b00);

			msleep(50);

			/* Enable VMID at 2x50k */
			snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x1f02);

			msleep(100);

			/* Enable VREF */
			snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x1f03);

			msleep(600);

			/* Enable BUFIOEN */
			snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL |
				     WM8990_BUFIOEN);

			/* Disable outputs */
			snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x3);

			/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
			snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_BUFIOEN);

			/* Enable workaround for ADC clocking issue. */
			snd_soc_component_write(component, WM8990_EXT_ACCESS_ENA, 0x2);
			snd_soc_component_write(component, WM8990_EXT_CTL1, 0xa003);
			snd_soc_component_write(component, WM8990_EXT_ACCESS_ENA, 0);
		}

		/* VMID=2*250k */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x4);
		break;

	case SND_SOC_BIAS_OFF:
		/* Enable POBCTRL and SOFT_ST */
		snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_POBCTRL | WM8990_BUFIOEN);

		/* Enable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_write(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_BUFDCOPEN | WM8990_POBCTRL |
			WM8990_BUFIOEN);

		/* mute DAC */
		snd_soc_component_update_bits(component, WM8990_DAC_CTRL,
				    WM8990_DAC_MUTE, WM8990_DAC_MUTE);

		/* Enable any disabled outputs */
		snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x1f03);

		/* Disable VMID */
		snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x1f01);

		msleep(300);

		/* Enable all output discharge bits */
		snd_soc_component_write(component, WM8990_ANTIPOP1, WM8990_DIS_LLINE |
			WM8990_DIS_RLINE | WM8990_DIS_OUT3 |
			WM8990_DIS_OUT4 | WM8990_DIS_LOUT |
			WM8990_DIS_ROUT);

		/* Disable VREF */
		snd_soc_component_write(component, WM8990_POWER_MANAGEMENT_1, 0x0);

		/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_write(component, WM8990_ANTIPOP2, 0x0);

		regcache_mark_dirty(wm8990->regmap);
		break;
	}

	return 0;
}