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
struct wm8983_priv {int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int WM8983_BIASEN ; 
 int WM8983_BIASEN_MASK ; 
 int WM8983_DELEN ; 
 int WM8983_DELEN_MASK ; 
 int /*<<< orphan*/  WM8983_OUT4_TO_ADC ; 
 int /*<<< orphan*/  WM8983_OUTPUT_CTRL ; 
 int WM8983_POBCTRL ; 
 int WM8983_POBCTRL_MASK ; 
 int /*<<< orphan*/  WM8983_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8983_POWER_MANAGEMENT_2 ; 
 int /*<<< orphan*/  WM8983_POWER_MANAGEMENT_3 ; 
 int WM8983_TSDEN ; 
 int WM8983_TSDEN_MASK ; 
 int WM8983_VMIDSEL_MASK ; 
 int WM8983_VMIDSEL_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8983_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8983_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8983_priv *wm8983 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		/* VMID at 100k */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK,
				    1 << WM8983_VMIDSEL_SHIFT);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regcache_sync(wm8983->regmap);
			if (ret < 0) {
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				return ret;
			}
			/* enable anti-pop features */
			snd_soc_component_update_bits(component, WM8983_OUT4_TO_ADC,
					    WM8983_POBCTRL_MASK | WM8983_DELEN_MASK,
					    WM8983_POBCTRL | WM8983_DELEN);
			/* enable thermal shutdown */
			snd_soc_component_update_bits(component, WM8983_OUTPUT_CTRL,
					    WM8983_TSDEN_MASK, WM8983_TSDEN);
			/* enable BIASEN */
			snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
					    WM8983_BIASEN_MASK, WM8983_BIASEN);
			/* VMID at 100k */
			snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
					    WM8983_VMIDSEL_MASK,
					    1 << WM8983_VMIDSEL_SHIFT);
			msleep(250);
			/* disable anti-pop features */
			snd_soc_component_update_bits(component, WM8983_OUT4_TO_ADC,
					    WM8983_POBCTRL_MASK |
					    WM8983_DELEN_MASK, 0);
		}

		/* VMID at 500k */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK,
				    2 << WM8983_VMIDSEL_SHIFT);
		break;
	case SND_SOC_BIAS_OFF:
		/* disable thermal shutdown */
		snd_soc_component_update_bits(component, WM8983_OUTPUT_CTRL,
				    WM8983_TSDEN_MASK, 0);
		/* disable VMIDSEL and BIASEN */
		snd_soc_component_update_bits(component, WM8983_POWER_MANAGEMENT_1,
				    WM8983_VMIDSEL_MASK | WM8983_BIASEN_MASK,
				    0);
		/* wait for VMID to discharge */
		msleep(100);
		snd_soc_component_write(component, WM8983_POWER_MANAGEMENT_1, 0);
		snd_soc_component_write(component, WM8983_POWER_MANAGEMENT_2, 0);
		snd_soc_component_write(component, WM8983_POWER_MANAGEMENT_3, 0);
		break;
	}

	return 0;
}