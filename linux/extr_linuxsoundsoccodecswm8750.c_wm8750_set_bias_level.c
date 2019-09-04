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
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8750_PWR1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_soc_component_cache_sync (struct snd_soc_component*) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8750_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	u16 pwr_reg = snd_soc_component_read32(component, WM8750_PWR1) & 0xfe3e;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_write(component, WM8750_PWR1, pwr_reg | 0x00c0);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_cache_sync(component);

			/* Set VMID to 5k */
			snd_soc_component_write(component, WM8750_PWR1, pwr_reg | 0x01c1);

			/* ...and ramp */
			msleep(1000);
		}

		/* mute dac and set vmid to 500k, enable VREF */
		snd_soc_component_write(component, WM8750_PWR1, pwr_reg | 0x0141);
		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, WM8750_PWR1, 0x0001);
		break;
	}
	return 0;
}