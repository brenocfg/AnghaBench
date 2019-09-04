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
struct rt5645_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  codec_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_TYPE_RT5645 ; 
 int RT5645_CP_FQ1_MASK ; 
 int RT5645_CP_FQ1_SFT ; 
 int RT5645_CP_FQ2_MASK ; 
 int RT5645_CP_FQ2_SFT ; 
 int RT5645_CP_FQ3_MASK ; 
 int RT5645_CP_FQ3_SFT ; 
 int RT5645_CP_FQ_12_KHZ ; 
 int RT5645_CP_FQ_192_KHZ ; 
 int RT5645_CP_FQ_96_KHZ ; 
 int /*<<< orphan*/  RT5645_DEPOP_M1 ; 
 int /*<<< orphan*/  RT5645_DEPOP_M3 ; 
 int RT5645_HP_L_SMT_DIS ; 
 int RT5645_HP_L_SMT_EN ; 
 int RT5645_HP_L_SMT_MASK ; 
 int RT5645_HP_R_SMT_DIS ; 
 int RT5645_HP_R_SMT_EN ; 
 int RT5645_HP_R_SMT_MASK ; 
 int RT5645_HP_SG_DIS ; 
 int RT5645_HP_SG_EN ; 
 int RT5645_HP_SG_MASK ; 
 scalar_t__ RT5645_MAMP_INT_REG2 ; 
 scalar_t__ RT5645_PR_BASE ; 
 int RT5645_RSTN_DIS ; 
 int RT5645_RSTN_EN ; 
 int RT5645_RSTN_MASK ; 
 int RT5645_RSTP_DIS ; 
 int RT5645_RSTP_EN ; 
 int RT5645_RSTP_MASK ; 
 int RT5645_SMT_TRIG_EN ; 
 int RT5645_SMT_TRIG_MASK ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  hp_amp_power (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5645_hp_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		hp_amp_power(component, 1);
		/* headphone unmute sequence */
		if (rt5645->codec_type == CODEC_TYPE_RT5645) {
			snd_soc_component_update_bits(component, RT5645_DEPOP_M3,
				RT5645_CP_FQ1_MASK | RT5645_CP_FQ2_MASK |
				RT5645_CP_FQ3_MASK,
				(RT5645_CP_FQ_192_KHZ << RT5645_CP_FQ1_SFT) |
				(RT5645_CP_FQ_12_KHZ << RT5645_CP_FQ2_SFT) |
				(RT5645_CP_FQ_192_KHZ << RT5645_CP_FQ3_SFT));
			regmap_write(rt5645->regmap, RT5645_PR_BASE +
				RT5645_MAMP_INT_REG2, 0xfc00);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_SMT_TRIG_MASK, RT5645_SMT_TRIG_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTN_MASK, RT5645_RSTN_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTN_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_RSTN_DIS |
				RT5645_HP_L_SMT_EN | RT5645_HP_R_SMT_EN);
			msleep(40);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_HP_SG_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_HP_SG_DIS |
				RT5645_HP_L_SMT_DIS | RT5645_HP_R_SMT_DIS);
		}
		break;

	case SND_SOC_DAPM_PRE_PMD:
		/* headphone mute sequence */
		if (rt5645->codec_type == CODEC_TYPE_RT5645) {
			snd_soc_component_update_bits(component, RT5645_DEPOP_M3,
				RT5645_CP_FQ1_MASK | RT5645_CP_FQ2_MASK |
				RT5645_CP_FQ3_MASK,
				(RT5645_CP_FQ_96_KHZ << RT5645_CP_FQ1_SFT) |
				(RT5645_CP_FQ_12_KHZ << RT5645_CP_FQ2_SFT) |
				(RT5645_CP_FQ_96_KHZ << RT5645_CP_FQ3_SFT));
			regmap_write(rt5645->regmap, RT5645_PR_BASE +
				RT5645_MAMP_INT_REG2, 0xfc00);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_HP_SG_MASK, RT5645_HP_SG_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTP_MASK, RT5645_RSTP_EN);
			snd_soc_component_update_bits(component, RT5645_DEPOP_M1,
				RT5645_RSTP_MASK | RT5645_HP_L_SMT_MASK |
				RT5645_HP_R_SMT_MASK, RT5645_RSTP_DIS |
				RT5645_HP_L_SMT_EN | RT5645_HP_R_SMT_EN);
			msleep(30);
		}
		hp_amp_power(component, 0);
		break;

	default:
		return 0;
	}

	return 0;
}