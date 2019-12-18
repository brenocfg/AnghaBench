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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8974_POWER1 ; 
 int WM8974_POWER1_BIASEN ; 
 int WM8974_POWER1_BUFIOEN ; 
 int /*<<< orphan*/  WM8974_POWER2 ; 
 int /*<<< orphan*/  WM8974_POWER3 ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8974_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	u16 power1 = snd_soc_component_read32(component, WM8974_POWER1) & ~0x3;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		power1 |= 0x1;  /* VMID 50k */
		snd_soc_component_write(component, WM8974_POWER1, power1);
		break;

	case SND_SOC_BIAS_STANDBY:
		power1 |= WM8974_POWER1_BIASEN | WM8974_POWER1_BUFIOEN;

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_sync(dev_get_regmap(component->dev, NULL));

			/* Initial cap charge at VMID 5k */
			snd_soc_component_write(component, WM8974_POWER1, power1 | 0x3);
			mdelay(100);
		}

		power1 |= 0x2;  /* VMID 500k */
		snd_soc_component_write(component, WM8974_POWER1, power1);
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, WM8974_POWER1, 0);
		snd_soc_component_write(component, WM8974_POWER2, 0);
		snd_soc_component_write(component, WM8974_POWER3, 0);
		break;
	}

	return 0;
}