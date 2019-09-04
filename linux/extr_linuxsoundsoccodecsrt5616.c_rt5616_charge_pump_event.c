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

/* Variables and functions */
 scalar_t__ RT5616_CHARGE_PUMP ; 
 scalar_t__ RT5616_CHOP_DAC_ADC ; 
 scalar_t__ RT5616_DEPOP_M1 ; 
 scalar_t__ RT5616_DEPOP_M2 ; 
 int RT5616_DEPOP_MAN ; 
 int RT5616_DEPOP_MASK ; 
 int RT5616_HP_CB_MASK ; 
 int RT5616_HP_CB_PD ; 
 int RT5616_HP_CB_PU ; 
 int RT5616_HP_CD_PD_EN ; 
 int RT5616_HP_CD_PD_MASK ; 
 int RT5616_HP_CO_DIS ; 
 int RT5616_HP_CO_EN ; 
 int RT5616_HP_CO_MASK ; 
 int RT5616_HP_CP_MASK ; 
 int RT5616_HP_CP_PD ; 
 int RT5616_HP_CP_PU ; 
 scalar_t__ RT5616_HP_DCC_INT1 ; 
 int RT5616_HP_L_SMT_DIS ; 
 int RT5616_HP_L_SMT_MASK ; 
 int RT5616_HP_R_SMT_DIS ; 
 int RT5616_HP_R_SMT_MASK ; 
 int RT5616_HP_SG_DIS ; 
 int RT5616_HP_SG_EN ; 
 int RT5616_HP_SG_MASK ; 
 int RT5616_PM_HP_HV ; 
 int RT5616_PM_HP_MASK ; 
 scalar_t__ RT5616_PR_BASE ; 
 scalar_t__ RT5616_PWR_ANLG1 ; 
 int RT5616_PWR_FV1 ; 
 int RT5616_PWR_FV2 ; 
 int RT5616_PWR_HA ; 
 int RT5616_PWR_HP_L ; 
 int RT5616_PWR_HP_R ; 
 int RT5616_PWR_HV_L ; 
 int RT5616_PWR_HV_R ; 
 scalar_t__ RT5616_PWR_VOL ; 
 int RT5616_SMT_TRIG_DIS ; 
 int RT5616_SMT_TRIG_MASK ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5616_charge_pump_event(struct snd_soc_dapm_widget *w,
				    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* depop parameters */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M2,
				    RT5616_DEPOP_MASK, RT5616_DEPOP_MAN);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_CP_MASK | RT5616_HP_SG_MASK |
				    RT5616_HP_CB_MASK, RT5616_HP_CP_PU |
				    RT5616_HP_SG_DIS | RT5616_HP_CB_PU);
		snd_soc_component_write(component, RT5616_PR_BASE +
			      RT5616_HP_DCC_INT1, 0x9f00);
		/* headphone amp power on */
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2, 0);
		snd_soc_component_update_bits(component, RT5616_PWR_VOL,
				    RT5616_PWR_HV_L | RT5616_PWR_HV_R,
				    RT5616_PWR_HV_L | RT5616_PWR_HV_R);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_HP_L | RT5616_PWR_HP_R |
				    RT5616_PWR_HA, RT5616_PWR_HP_L |
				    RT5616_PWR_HP_R | RT5616_PWR_HA);
		msleep(50);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2,
				    RT5616_PWR_FV1 | RT5616_PWR_FV2);

		snd_soc_component_update_bits(component, RT5616_CHARGE_PUMP,
				    RT5616_PM_HP_MASK, RT5616_PM_HP_HV);
		snd_soc_component_update_bits(component, RT5616_PR_BASE +
				    RT5616_CHOP_DAC_ADC, 0x0200, 0x0200);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_CO_MASK | RT5616_HP_SG_MASK,
				    RT5616_HP_CO_EN | RT5616_HP_SG_EN);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, RT5616_PR_BASE +
				    RT5616_CHOP_DAC_ADC, 0x0200, 0x0);
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_HP_SG_MASK | RT5616_HP_L_SMT_MASK |
				    RT5616_HP_R_SMT_MASK, RT5616_HP_SG_DIS |
				    RT5616_HP_L_SMT_DIS | RT5616_HP_R_SMT_DIS);
		/* headphone amp power down */
		snd_soc_component_update_bits(component, RT5616_DEPOP_M1,
				    RT5616_SMT_TRIG_MASK |
				    RT5616_HP_CD_PD_MASK | RT5616_HP_CO_MASK |
				    RT5616_HP_CP_MASK | RT5616_HP_SG_MASK |
				    RT5616_HP_CB_MASK,
				    RT5616_SMT_TRIG_DIS | RT5616_HP_CD_PD_EN |
				    RT5616_HP_CO_DIS | RT5616_HP_CP_PD |
				    RT5616_HP_SG_EN | RT5616_HP_CB_PD);
		snd_soc_component_update_bits(component, RT5616_PWR_ANLG1,
				    RT5616_PWR_HP_L | RT5616_PWR_HP_R |
				    RT5616_PWR_HA, 0);
		break;
	default:
		return 0;
	}

	return 0;
}