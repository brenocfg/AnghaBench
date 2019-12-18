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
struct rt5663_priv {int /*<<< orphan*/  codec_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_VER_1 ; 
 int /*<<< orphan*/  RT5663_ANA_BIAS_CUR_1 ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_CHARGE_PUMP_2 ; 
 int /*<<< orphan*/  RT5663_DACREF_LDO ; 
 int /*<<< orphan*/  RT5663_DEPOP_1 ; 
 int /*<<< orphan*/  RT5663_DEPOP_2 ; 
 int /*<<< orphan*/  RT5663_DIG_VOL_ZCD ; 
 int /*<<< orphan*/  RT5663_HP_BIAS ; 
 int /*<<< orphan*/  RT5663_HP_CHARGE_PUMP_1 ; 
 int /*<<< orphan*/  RT5663_HP_CHARGE_PUMP_2 ; 
 int /*<<< orphan*/  RT5663_HP_LOGIC_2 ; 
 int RT5663_HP_SIG_SRC1_MASK ; 
 int RT5663_HP_SIG_SRC1_REG ; 
 int RT5663_HP_SIG_SRC1_SILENCE ; 
 int RT5663_OVCD_HP_DIS ; 
 int RT5663_OVCD_HP_EN ; 
 int RT5663_OVCD_HP_MASK ; 
 int RT5663_SEL_PM_HP_HIGH ; 
 int RT5663_SEL_PM_HP_SHIFT ; 
 int /*<<< orphan*/  RT5663_STO_DRE_1 ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5663_hp_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (rt5663->codec_ver == CODEC_VER_1) {
			snd_soc_component_update_bits(component, RT5663_HP_CHARGE_PUMP_1,
				RT5663_SEL_PM_HP_SHIFT, RT5663_SEL_PM_HP_HIGH);
			snd_soc_component_update_bits(component, RT5663_HP_LOGIC_2,
				RT5663_HP_SIG_SRC1_MASK,
				RT5663_HP_SIG_SRC1_SILENCE);
		} else {
			snd_soc_component_update_bits(component,
				RT5663_DACREF_LDO, 0x3e0e, 0x3a0a);
			snd_soc_component_write(component, RT5663_DEPOP_2, 0x3003);
			snd_soc_component_update_bits(component, RT5663_HP_CHARGE_PUMP_1,
				RT5663_OVCD_HP_MASK, RT5663_OVCD_HP_DIS);
			snd_soc_component_write(component, RT5663_HP_CHARGE_PUMP_2, 0x1371);
			snd_soc_component_write(component, RT5663_HP_BIAS, 0xabba);
			snd_soc_component_write(component, RT5663_CHARGE_PUMP_1, 0x2224);
			snd_soc_component_write(component, RT5663_ANA_BIAS_CUR_1, 0x7766);
			snd_soc_component_write(component, RT5663_HP_BIAS, 0xafaa);
			snd_soc_component_write(component, RT5663_CHARGE_PUMP_2, 0x7777);
			snd_soc_component_update_bits(component, RT5663_STO_DRE_1, 0x8000,
				0x8000);
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x3000,
				0x3000);
			snd_soc_component_update_bits(component,
				RT5663_DIG_VOL_ZCD, 0x00c0, 0x0080);
		}
		break;

	case SND_SOC_DAPM_PRE_PMD:
		if (rt5663->codec_ver == CODEC_VER_1) {
			snd_soc_component_update_bits(component, RT5663_HP_LOGIC_2,
				RT5663_HP_SIG_SRC1_MASK,
				RT5663_HP_SIG_SRC1_REG);
		} else {
			snd_soc_component_update_bits(component, RT5663_DEPOP_1, 0x3000, 0x0);
			snd_soc_component_update_bits(component, RT5663_HP_CHARGE_PUMP_1,
				RT5663_OVCD_HP_MASK, RT5663_OVCD_HP_EN);
			snd_soc_component_update_bits(component,
				RT5663_DACREF_LDO, 0x3e0e, 0);
			snd_soc_component_update_bits(component,
				RT5663_DIG_VOL_ZCD, 0x00c0, 0);
		}
		break;

	default:
		return 0;
	}

	return 0;
}