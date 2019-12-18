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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct rt5670_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5670_CHARGE_PUMP ; 
 scalar_t__ RT5670_DEPOP_M1 ; 
 scalar_t__ RT5670_DEPOP_M2 ; 
 int /*<<< orphan*/  RT5670_GEN_CTRL2 ; 
 scalar_t__ RT5670_HP_DCC_INT1 ; 
 int RT5670_PM_HP_HV ; 
 int RT5670_PM_HP_MASK ; 
 scalar_t__ RT5670_PR_BASE ; 
 int /*<<< orphan*/  RT5670_PWR_ANLG1 ; 
 int RT5670_PWR_FV1 ; 
 int RT5670_PWR_FV2 ; 
 int RT5670_PWR_HA ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct rt5670_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5670_hp_power_event(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5670_priv *rt5670 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(rt5670->regmap, RT5670_CHARGE_PUMP,
			RT5670_PM_HP_MASK, RT5670_PM_HP_HV);
		regmap_update_bits(rt5670->regmap, RT5670_GEN_CTRL2,
			0x0400, 0x0400);
		/* headphone amp power on */
		regmap_update_bits(rt5670->regmap, RT5670_PWR_ANLG1,
			RT5670_PWR_HA |	RT5670_PWR_FV1 |
			RT5670_PWR_FV2,	RT5670_PWR_HA |
			RT5670_PWR_FV1 | RT5670_PWR_FV2);
		/* depop parameters */
		regmap_write(rt5670->regmap, RT5670_DEPOP_M2, 0x3100);
		regmap_write(rt5670->regmap, RT5670_DEPOP_M1, 0x8009);
		regmap_write(rt5670->regmap, RT5670_PR_BASE +
			RT5670_HP_DCC_INT1, 0x9f00);
		mdelay(20);
		regmap_write(rt5670->regmap, RT5670_DEPOP_M1, 0x8019);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		regmap_write(rt5670->regmap, RT5670_DEPOP_M1, 0x0004);
		msleep(30);
		break;
	default:
		return 0;
	}

	return 0;
}