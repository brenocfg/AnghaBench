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
#define  RT5665_ADC_MONO_L_ASRC_SFT 138 
#define  RT5665_ADC_MONO_R_ASRC_SFT 137 
#define  RT5665_ADC_STO1_ASRC_SFT 136 
#define  RT5665_ADC_STO2_ASRC_SFT 135 
 int /*<<< orphan*/  RT5665_ADDA_CLK_1 ; 
 unsigned int RT5665_AD_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5665_AD_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5665_AD_STO1_CLK_SEL_SFT ; 
 unsigned int RT5665_AD_STO2_CLK_SEL_SFT ; 
 unsigned int RT5665_ASRC_2 ; 
 unsigned int RT5665_ASRC_3 ; 
#define  RT5665_CLK_SEL_I2S1_ASRC 134 
#define  RT5665_CLK_SEL_I2S2_ASRC 133 
#define  RT5665_CLK_SEL_I2S3_ASRC 132 
#define  RT5665_DAC_MONO_L_ASRC_SFT 131 
#define  RT5665_DAC_MONO_R_ASRC_SFT 130 
#define  RT5665_DAC_STO1_ASRC_SFT 129 
#define  RT5665_DAC_STO2_ASRC_SFT 128 
 unsigned int RT5665_DA_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5665_DA_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5665_DA_STO1_CLK_SEL_SFT ; 
 unsigned int RT5665_DA_STO2_CLK_SEL_SFT ; 
 int /*<<< orphan*/  RT5665_I2S_PD1_2 ; 
 int /*<<< orphan*/  RT5665_I2S_PD1_MASK ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_using_asrc(struct snd_soc_dapm_widget *w,
			 struct snd_soc_dapm_widget *sink)
{
	unsigned int reg, shift, val;
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (w->shift) {
	case RT5665_ADC_MONO_R_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shift = RT5665_AD_MONOR_CLK_SEL_SFT;
		break;
	case RT5665_ADC_MONO_L_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shift = RT5665_AD_MONOL_CLK_SEL_SFT;
		break;
	case RT5665_ADC_STO1_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shift = RT5665_AD_STO1_CLK_SEL_SFT;
		break;
	case RT5665_ADC_STO2_ASRC_SFT:
		reg = RT5665_ASRC_3;
		shift = RT5665_AD_STO2_CLK_SEL_SFT;
		break;
	case RT5665_DAC_MONO_R_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shift = RT5665_DA_MONOR_CLK_SEL_SFT;
		break;
	case RT5665_DAC_MONO_L_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shift = RT5665_DA_MONOL_CLK_SEL_SFT;
		break;
	case RT5665_DAC_STO1_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shift = RT5665_DA_STO1_CLK_SEL_SFT;
		break;
	case RT5665_DAC_STO2_ASRC_SFT:
		reg = RT5665_ASRC_2;
		shift = RT5665_DA_STO2_CLK_SEL_SFT;
		break;
	default:
		return 0;
	}

	val = (snd_soc_component_read32(component, reg) >> shift) & 0xf;
	switch (val) {
	case RT5665_CLK_SEL_I2S1_ASRC:
	case RT5665_CLK_SEL_I2S2_ASRC:
	case RT5665_CLK_SEL_I2S3_ASRC:
		/* I2S_Pre_Div1 should be 1 in asrc mode */
		snd_soc_component_update_bits(component, RT5665_ADDA_CLK_1,
			RT5665_I2S_PD1_MASK, RT5665_I2S_PD1_2);
		return 1;
	default:
		return 0;
	}

}