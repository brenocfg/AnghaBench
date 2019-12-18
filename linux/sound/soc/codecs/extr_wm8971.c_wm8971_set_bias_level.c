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
struct wm8971_priv {int /*<<< orphan*/  charge_work; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8971_PWR1 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_cache_sync (struct snd_soc_component*) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8971_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int wm8971_set_bias_level(struct snd_soc_component *component,
	enum snd_soc_bias_level level)
{
	struct wm8971_priv *wm8971 = snd_soc_component_get_drvdata(component);
	u16 pwr_reg = snd_soc_component_read32(component, WM8971_PWR1) & 0xfe3e;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_write(component, WM8971_PWR1, pwr_reg | 0x00c1);
		break;
	case SND_SOC_BIAS_PREPARE:
		/* Wait until fully charged */
		flush_delayed_work(&wm8971->charge_work);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_cache_sync(component);
			/* charge output caps - set vmid to 5k for quick power up */
			snd_soc_component_write(component, WM8971_PWR1, pwr_reg | 0x01c0);
			queue_delayed_work(system_power_efficient_wq,
				&wm8971->charge_work, msecs_to_jiffies(1000));
		} else {
			/* mute dac and set vmid to 500k, enable VREF */
			snd_soc_component_write(component, WM8971_PWR1, pwr_reg | 0x0140);
		}

		break;
	case SND_SOC_BIAS_OFF:
		cancel_delayed_work_sync(&wm8971->charge_work);
		snd_soc_component_write(component, WM8971_PWR1, 0x0001);
		break;
	}
	return 0;
}