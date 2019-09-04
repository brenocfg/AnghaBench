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
struct wm8985_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int WM8985_BIASEN ; 
 int WM8985_BIASEN_MASK ; 
 int /*<<< orphan*/  WM8985_OUT4_TO_ADC ; 
 int /*<<< orphan*/  WM8985_OUTPUT_CTRL0 ; 
 int WM8985_POBCTRL ; 
 int WM8985_POBCTRL_MASK ; 
 int /*<<< orphan*/  WM8985_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8985_POWER_MANAGEMENT_2 ; 
 int /*<<< orphan*/  WM8985_POWER_MANAGEMENT_3 ; 
 int WM8985_TSDEN ; 
 int WM8985_TSDEN_MASK ; 
 int WM8985_TSOPCTRL ; 
 int WM8985_TSOPCTRL_MASK ; 
 int WM8985_VMIDSEL_MASK ; 
 int WM8985_VMIDSEL_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8985_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8985_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	int ret;
	struct wm8985_priv *wm8985;

	wm8985 = snd_soc_component_get_drvdata(component);
	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		/* VMID at 75k */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK,
				    1 << WM8985_VMIDSEL_SHIFT);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8985->supplies),
						    wm8985->supplies);
			if (ret) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}

			regcache_sync(wm8985->regmap);

			/* enable anti-pop features */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTRL_MASK,
					    WM8985_POBCTRL);
			/* enable thermal shutdown */
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
					    WM8985_TSDEN_MASK, WM8985_TSDEN);
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
					    WM8985_TSOPCTRL_MASK,
					    WM8985_TSOPCTRL);
			/* enable BIASEN */
			snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
					    WM8985_BIASEN_MASK, WM8985_BIASEN);
			/* VMID at 75k */
			snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
					    WM8985_VMIDSEL_MASK,
					    1 << WM8985_VMIDSEL_SHIFT);
			msleep(500);
			/* disable anti-pop features */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTRL_MASK, 0);
		}
		/* VMID at 300k */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK,
				    2 << WM8985_VMIDSEL_SHIFT);
		break;
	case SND_SOC_BIAS_OFF:
		/* disable thermal shutdown */
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
				    WM8985_TSOPCTRL_MASK, 0);
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTRL0,
				    WM8985_TSDEN_MASK, 0);
		/* disable VMIDSEL and BIASEN */
		snd_soc_component_update_bits(component, WM8985_POWER_MANAGEMENT_1,
				    WM8985_VMIDSEL_MASK | WM8985_BIASEN_MASK,
				    0);
		snd_soc_component_write(component, WM8985_POWER_MANAGEMENT_1, 0);
		snd_soc_component_write(component, WM8985_POWER_MANAGEMENT_2, 0);
		snd_soc_component_write(component, WM8985_POWER_MANAGEMENT_3, 0);

		regcache_mark_dirty(wm8985->regmap);

		regulator_bulk_disable(ARRAY_SIZE(wm8985->supplies),
				       wm8985->supplies);
		break;
	}

	return 0;
}