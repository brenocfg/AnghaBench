#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  jd_mode; } ;
struct rt5670_priv {TYPE_1__ pdata; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  RT5670_CHARGE_PUMP ; 
 int /*<<< orphan*/  RT5670_DIG_MISC ; 
 int RT5670_LDO_SEL_MASK ; 
 int RT5670_OSW_L_DIS ; 
 int RT5670_OSW_L_MASK ; 
 int RT5670_OSW_R_DIS ; 
 int RT5670_OSW_R_MASK ; 
 int /*<<< orphan*/  RT5670_PWR_ANLG1 ; 
 int RT5670_PWR_BG ; 
 int RT5670_PWR_FV1 ; 
 int RT5670_PWR_FV2 ; 
 int RT5670_PWR_MB ; 
 int RT5670_PWR_VREF1 ; 
 int RT5670_PWR_VREF2 ; 
#define  SND_SOC_BIAS_OFF 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt5670_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rt5670_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_component_get_bias_level(component)) {
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2);
			mdelay(10);
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_FV1 | RT5670_PWR_FV2);
			snd_soc_component_update_bits(component, RT5670_CHARGE_PUMP,
				RT5670_OSW_L_MASK | RT5670_OSW_R_MASK,
				RT5670_OSW_L_DIS | RT5670_OSW_R_DIS);
			snd_soc_component_update_bits(component, RT5670_DIG_MISC, 0x1, 0x1);
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x5);
		}
		break;
	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);
		snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x3);
		break;
	case SND_SOC_BIAS_OFF:
		if (rt5670->pdata.jd_mode)
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_MB | RT5670_PWR_BG);
		else
			snd_soc_component_update_bits(component, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);

		snd_soc_component_update_bits(component, RT5670_DIG_MISC, 0x1, 0x0);
		break;

	default:
		break;
	}

	return 0;
}