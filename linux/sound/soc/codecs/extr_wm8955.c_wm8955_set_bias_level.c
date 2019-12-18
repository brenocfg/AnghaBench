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
struct wm8955_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  WM8955_ADDITIONAL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8955_ADDITIONAL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8955_POWER_MANAGEMENT_1 ; 
 int WM8955_VMIDSEL_MASK ; 
 int WM8955_VMIDSEL_SHIFT ; 
 int WM8955_VREF ; 
 int WM8955_VREF_SHIFT ; 
 int WM8955_VROI ; 
 int WM8955_VSEL_MASK ; 
 int WM8955_VSEL_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8955_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8955_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8955_priv *wm8955 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* VMID resistance 2*50k */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VMIDSEL_MASK,
				    0x1 << WM8955_VMIDSEL_SHIFT);

		/* Default bias current */
		snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_1,
				    WM8955_VSEL_MASK,
				    0x2 << WM8955_VSEL_SHIFT);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8955->supplies),
						    wm8955->supplies);
			if (ret != 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}

			regcache_sync(wm8955->regmap);

			/* Enable VREF and VMID */
			snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
					    WM8955_VREF |
					    WM8955_VMIDSEL_MASK,
					    WM8955_VREF |
					    0x3 << WM8955_VREF_SHIFT);

			/* Let VMID ramp */
			msleep(500);

			/* High resistance VROI to maintain outputs */
			snd_soc_component_update_bits(component,
					    WM8955_ADDITIONAL_CONTROL_3,
					    WM8955_VROI, WM8955_VROI);
		}

		/* Maintain VMID with 2*250k */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VMIDSEL_MASK,
				    0x2 << WM8955_VMIDSEL_SHIFT);

		/* Minimum bias current */
		snd_soc_component_update_bits(component, WM8955_ADDITIONAL_CONTROL_1,
				    WM8955_VSEL_MASK, 0);
		break;

	case SND_SOC_BIAS_OFF:
		/* Low resistance VROI to help discharge */
		snd_soc_component_update_bits(component,
				    WM8955_ADDITIONAL_CONTROL_3,
				    WM8955_VROI, 0);

		/* Turn off VMID and VREF */
		snd_soc_component_update_bits(component, WM8955_POWER_MANAGEMENT_1,
				    WM8955_VREF |
				    WM8955_VMIDSEL_MASK, 0);

		regulator_bulk_disable(ARRAY_SIZE(wm8955->supplies),
				       wm8955->supplies);
		break;
	}
	return 0;
}