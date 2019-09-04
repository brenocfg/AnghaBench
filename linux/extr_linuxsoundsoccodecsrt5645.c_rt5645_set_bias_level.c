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
struct snd_soc_component {int dummy; } ;
struct rt5645_priv {int /*<<< orphan*/  en_button_func; int /*<<< orphan*/  jack_detect_work; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  RT5645_DEPOP_M2 ; 
 int RT5645_DIG_GATE_CTRL ; 
 int /*<<< orphan*/  RT5645_GEN_CTRL1 ; 
 int /*<<< orphan*/  RT5645_PWR_ANLG1 ; 
 int RT5645_PWR_BG ; 
 int RT5645_PWR_FV1 ; 
 int RT5645_PWR_FV2 ; 
 int RT5645_PWR_MB ; 
 int RT5645_PWR_VREF1 ; 
 int RT5645_PWR_VREF2 ; 
#define  SND_SOC_BIAS_OFF 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int rt5645_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_level(component)) {
			snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2);
			mdelay(10);
			snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_FV1 | RT5645_PWR_FV2,
				RT5645_PWR_FV1 | RT5645_PWR_FV2);
			snd_soc_component_update_bits(component, RT5645_GEN_CTRL1,
				RT5645_DIG_GATE_CTRL, RT5645_DIG_GATE_CTRL);
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_VREF1 | RT5645_PWR_MB |
			RT5645_PWR_BG | RT5645_PWR_VREF2,
			RT5645_PWR_VREF1 | RT5645_PWR_MB |
			RT5645_PWR_BG | RT5645_PWR_VREF2);
		mdelay(10);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
			RT5645_PWR_FV1 | RT5645_PWR_FV2,
			RT5645_PWR_FV1 | RT5645_PWR_FV2);
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_write(component, RT5645_DEPOP_M2, 0x1140);
			msleep(40);
			if (rt5645->en_button_func)
				queue_delayed_work(system_power_efficient_wq,
					&rt5645->jack_detect_work,
					msecs_to_jiffies(0));
		}
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, RT5645_DEPOP_M2, 0x1100);
		if (!rt5645->en_button_func)
			snd_soc_component_update_bits(component, RT5645_GEN_CTRL1,
					RT5645_DIG_GATE_CTRL, 0);
		snd_soc_component_update_bits(component, RT5645_PWR_ANLG1,
				RT5645_PWR_VREF1 | RT5645_PWR_MB |
				RT5645_PWR_BG | RT5645_PWR_VREF2 |
				RT5645_PWR_FV1 | RT5645_PWR_FV2, 0x0);
		break;

	default:
		break;
	}

	return 0;
}