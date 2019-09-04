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
struct rt5640_priv {int asrc_en; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RT5640_ADC_M_MASK ; 
 unsigned int RT5640_ADC_M_SFT ; 
 unsigned int RT5640_AD_MONO_L_FILTER ; 
 unsigned int RT5640_AD_MONO_R_FILTER ; 
 unsigned int RT5640_AD_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5640_ASRC_2 ; 
#define  RT5640_CLK_SEL_ASRC 129 
#define  RT5640_CLK_SEL_SYS 128 
 unsigned int RT5640_DA_MONO_L_FILTER ; 
 unsigned int RT5640_DA_MONO_R_FILTER ; 
 unsigned int RT5640_DA_STEREO_FILTER ; 
 int /*<<< orphan*/  RT5640_JD_CTRL ; 
 unsigned int RT5640_MAD_L_M_MASK ; 
 unsigned int RT5640_MAD_L_M_SFT ; 
 unsigned int RT5640_MAD_R_M_MASK ; 
 unsigned int RT5640_MAD_R_M_SFT ; 
 unsigned int RT5640_MDA_L_M_MASK ; 
 unsigned int RT5640_MDA_L_M_SFT ; 
 unsigned int RT5640_MDA_R_M_MASK ; 
 unsigned int RT5640_MDA_R_M_SFT ; 
 unsigned int RT5640_STO_DAC_M_MASK ; 
 unsigned int RT5640_STO_DAC_M_SFT ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

int rt5640_sel_asrc_clk_src(struct snd_soc_component *component,
		unsigned int filter_mask, unsigned int clk_src)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	unsigned int asrc2_mask = 0;
	unsigned int asrc2_value = 0;

	switch (clk_src) {
	case RT5640_CLK_SEL_SYS:
	case RT5640_CLK_SEL_ASRC:
		break;

	default:
		return -EINVAL;
	}

	if (!filter_mask)
		return -EINVAL;

	if (filter_mask & RT5640_DA_STEREO_FILTER) {
		asrc2_mask |= RT5640_STO_DAC_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_STO_DAC_M_MASK)
			| (clk_src << RT5640_STO_DAC_M_SFT);
	}

	if (filter_mask & RT5640_DA_MONO_L_FILTER) {
		asrc2_mask |= RT5640_MDA_L_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MDA_L_M_MASK)
			| (clk_src << RT5640_MDA_L_M_SFT);
	}

	if (filter_mask & RT5640_DA_MONO_R_FILTER) {
		asrc2_mask |= RT5640_MDA_R_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MDA_R_M_MASK)
			| (clk_src << RT5640_MDA_R_M_SFT);
	}

	if (filter_mask & RT5640_AD_STEREO_FILTER) {
		asrc2_mask |= RT5640_ADC_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_ADC_M_MASK)
			| (clk_src << RT5640_ADC_M_SFT);
	}

	if (filter_mask & RT5640_AD_MONO_L_FILTER) {
		asrc2_mask |= RT5640_MAD_L_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MAD_L_M_MASK)
			| (clk_src << RT5640_MAD_L_M_SFT);
	}

	if (filter_mask & RT5640_AD_MONO_R_FILTER)  {
		asrc2_mask |= RT5640_MAD_R_M_MASK;
		asrc2_value = (asrc2_value & ~RT5640_MAD_R_M_MASK)
			| (clk_src << RT5640_MAD_R_M_SFT);
	}

	snd_soc_component_update_bits(component, RT5640_ASRC_2,
		asrc2_mask, asrc2_value);

	if (snd_soc_component_read32(component, RT5640_ASRC_2)) {
		rt5640->asrc_en = true;
		snd_soc_component_update_bits(component, RT5640_JD_CTRL, 0x3, 0x3);
	} else {
		rt5640->asrc_en = false;
		snd_soc_component_update_bits(component, RT5640_JD_CTRL, 0x3, 0x0);
	}

	return 0;
}