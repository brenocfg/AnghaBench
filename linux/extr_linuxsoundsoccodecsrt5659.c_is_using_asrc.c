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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  RT5659_ADC_MONO_L_ASRC_SFT 133 
#define  RT5659_ADC_MONO_R_ASRC_SFT 132 
#define  RT5659_ADC_STO1_ASRC_SFT 131 
 int /*<<< orphan*/  RT5659_ADDA_CLK_1 ; 
 unsigned int RT5659_AD_MONO_L_T_SFT ; 
 unsigned int RT5659_AD_MONO_R_T_SFT ; 
 unsigned int RT5659_AD_STO1_T_SFT ; 
 unsigned int RT5659_ASRC_2 ; 
 unsigned int RT5659_ASRC_3 ; 
#define  RT5659_DAC_MONO_L_ASRC_SFT 130 
#define  RT5659_DAC_MONO_R_ASRC_SFT 129 
#define  RT5659_DAC_STO_ASRC_SFT 128 
 unsigned int RT5659_DA_MONO_L_T_SFT ; 
 unsigned int RT5659_DA_MONO_R_T_SFT ; 
 unsigned int RT5659_DA_STO_T_SFT ; 
 int /*<<< orphan*/  RT5659_I2S_PD1_2 ; 
 int /*<<< orphan*/  RT5659_I2S_PD1_MASK ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_using_asrc(struct snd_soc_dapm_widget *w,
			 struct snd_soc_dapm_widget *sink)
{
	unsigned int reg, shift, val;
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (w->shift) {
	case RT5659_ADC_MONO_R_ASRC_SFT:
		reg = RT5659_ASRC_3;
		shift = RT5659_AD_MONO_R_T_SFT;
		break;
	case RT5659_ADC_MONO_L_ASRC_SFT:
		reg = RT5659_ASRC_3;
		shift = RT5659_AD_MONO_L_T_SFT;
		break;
	case RT5659_ADC_STO1_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shift = RT5659_AD_STO1_T_SFT;
		break;
	case RT5659_DAC_MONO_R_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shift = RT5659_DA_MONO_R_T_SFT;
		break;
	case RT5659_DAC_MONO_L_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shift = RT5659_DA_MONO_L_T_SFT;
		break;
	case RT5659_DAC_STO_ASRC_SFT:
		reg = RT5659_ASRC_2;
		shift = RT5659_DA_STO_T_SFT;
		break;
	default:
		return 0;
	}

	val = (snd_soc_component_read32(component, reg) >> shift) & 0xf;
	switch (val) {
	case 1:
	case 2:
	case 3:
		/* I2S_Pre_Div1 should be 1 in asrc mode */
		snd_soc_component_update_bits(component, RT5659_ADDA_CLK_1,
			RT5659_I2S_PD1_MASK, RT5659_I2S_PD1_2);
		return 1;
	default:
		return 0;
	}

}