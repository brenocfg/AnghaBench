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
struct wm8988_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8988_PWR1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8988_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8988_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);
	u16 pwr_reg = snd_soc_component_read32(component, WM8988_PWR1) & ~0x1c1;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VREF, VMID=2x50k, digital enabled */
		snd_soc_component_write(component, WM8988_PWR1, pwr_reg | 0x00c0);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_sync(wm8988->regmap);

			/* VREF, VMID=2x5k */
			snd_soc_component_write(component, WM8988_PWR1, pwr_reg | 0x1c1);

			/* Charge caps */
			msleep(100);
		}

		/* VREF, VMID=2*500k, digital stopped */
		snd_soc_component_write(component, WM8988_PWR1, pwr_reg | 0x0141);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, WM8988_PWR1, 0x0000);
		break;
	}
	return 0;
}