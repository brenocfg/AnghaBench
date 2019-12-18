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
struct wm8991_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8991_ANTIPOP1 ; 
 int /*<<< orphan*/  WM8991_ANTIPOP2 ; 
 int WM8991_BUFDCOPEN ; 
 int WM8991_BUFIOEN ; 
 int /*<<< orphan*/  WM8991_DAC_CTRL ; 
 int WM8991_DAC_MUTE ; 
 int WM8991_DIS_LLINE ; 
 int WM8991_DIS_LOUT ; 
 int WM8991_DIS_OUT3 ; 
 int WM8991_DIS_OUT4 ; 
 int WM8991_DIS_RLINE ; 
 int WM8991_DIS_ROUT ; 
 int WM8991_POBCTRL ; 
 int /*<<< orphan*/  WM8991_POWER_MANAGEMENT_1 ; 
 int WM8991_SOFTST ; 
 int WM8991_VMIDTOG ; 
 int WM8991_VMID_MODE_MASK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8991_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8991_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8991_priv *wm8991 = snd_soc_component_get_drvdata(component);
	u16 val;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID=2*50k */
		val = snd_soc_component_read32(component, WM8991_POWER_MANAGEMENT_1) &
		      ~WM8991_VMID_MODE_MASK;
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, val | 0x2);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_sync(wm8991->regmap);
			/* Enable all output discharge bits */
			snd_soc_component_write(component, WM8991_ANTIPOP1, WM8991_DIS_LLINE |
				      WM8991_DIS_RLINE | WM8991_DIS_OUT3 |
				      WM8991_DIS_OUT4 | WM8991_DIS_LOUT |
				      WM8991_DIS_ROUT);

			/* Enable POBCTRL, SOFT_ST, VMIDTOG and BUFDCOPEN */
			snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_SOFTST |
				      WM8991_BUFDCOPEN | WM8991_POBCTRL |
				      WM8991_VMIDTOG);

			/* Delay to allow output caps to discharge */
			msleep(300);

			/* Disable VMIDTOG */
			snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_SOFTST |
				      WM8991_BUFDCOPEN | WM8991_POBCTRL);

			/* disable all output discharge bits */
			snd_soc_component_write(component, WM8991_ANTIPOP1, 0);

			/* Enable outputs */
			snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x1b00);

			msleep(50);

			/* Enable VMID at 2x50k */
			snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x1f02);

			msleep(100);

			/* Enable VREF */
			snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x1f03);

			msleep(600);

			/* Enable BUFIOEN */
			snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_SOFTST |
				      WM8991_BUFDCOPEN | WM8991_POBCTRL |
				      WM8991_BUFIOEN);

			/* Disable outputs */
			snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x3);

			/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
			snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_BUFIOEN);
		}

		/* VMID=2*250k */
		val = snd_soc_component_read32(component, WM8991_POWER_MANAGEMENT_1) &
		      ~WM8991_VMID_MODE_MASK;
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, val | 0x4);
		break;

	case SND_SOC_BIAS_OFF:
		/* Enable POBCTRL and SOFT_ST */
		snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_SOFTST |
			      WM8991_POBCTRL | WM8991_BUFIOEN);

		/* Enable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_write(component, WM8991_ANTIPOP2, WM8991_SOFTST |
			      WM8991_BUFDCOPEN | WM8991_POBCTRL |
			      WM8991_BUFIOEN);

		/* mute DAC */
		val = snd_soc_component_read32(component, WM8991_DAC_CTRL);
		snd_soc_component_write(component, WM8991_DAC_CTRL, val | WM8991_DAC_MUTE);

		/* Enable any disabled outputs */
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x1f03);

		/* Disable VMID */
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x1f01);

		msleep(300);

		/* Enable all output discharge bits */
		snd_soc_component_write(component, WM8991_ANTIPOP1, WM8991_DIS_LLINE |
			      WM8991_DIS_RLINE | WM8991_DIS_OUT3 |
			      WM8991_DIS_OUT4 | WM8991_DIS_LOUT |
			      WM8991_DIS_ROUT);

		/* Disable VREF */
		snd_soc_component_write(component, WM8991_POWER_MANAGEMENT_1, 0x0);

		/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_write(component, WM8991_ANTIPOP2, 0x0);
		regcache_mark_dirty(wm8991->regmap);
		break;
	}

	return 0;
}