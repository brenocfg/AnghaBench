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

/* Variables and functions */
 int EINVAL ; 
 unsigned int RT5645_AD_MONOL_CLK_SEL_MASK ; 
 unsigned int RT5645_AD_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5645_AD_MONOR_CLK_SEL_MASK ; 
 unsigned int RT5645_AD_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5645_AD_MONO_L_FILTER ; 
 unsigned int RT5645_AD_MONO_R_FILTER ; 
 unsigned int RT5645_AD_STEREO_FILTER ; 
 unsigned int RT5645_AD_STO1_CLK_SEL_MASK ; 
 unsigned int RT5645_AD_STO1_CLK_SEL_SFT ; 
 int /*<<< orphan*/  RT5645_ASRC_2 ; 
 int /*<<< orphan*/  RT5645_ASRC_3 ; 
#define  RT5645_CLK_SEL_I2S1_ASRC 131 
#define  RT5645_CLK_SEL_I2S2_ASRC 130 
#define  RT5645_CLK_SEL_SYS 129 
#define  RT5645_CLK_SEL_SYS2 128 
 unsigned int RT5645_DA_MONOL_CLK_SEL_MASK ; 
 unsigned int RT5645_DA_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5645_DA_MONOR_CLK_SEL_MASK ; 
 unsigned int RT5645_DA_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5645_DA_MONO_L_FILTER ; 
 unsigned int RT5645_DA_MONO_R_FILTER ; 
 unsigned int RT5645_DA_STEREO_FILTER ; 
 unsigned int RT5645_DA_STO_CLK_SEL_MASK ; 
 unsigned int RT5645_DA_STO_CLK_SEL_SFT ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int rt5645_sel_asrc_clk_src(struct snd_soc_component *component,
		unsigned int filter_mask, unsigned int clk_src)
{
	unsigned int asrc2_mask = 0;
	unsigned int asrc2_value = 0;
	unsigned int asrc3_mask = 0;
	unsigned int asrc3_value = 0;

	switch (clk_src) {
	case RT5645_CLK_SEL_SYS:
	case RT5645_CLK_SEL_I2S1_ASRC:
	case RT5645_CLK_SEL_I2S2_ASRC:
	case RT5645_CLK_SEL_SYS2:
		break;

	default:
		return -EINVAL;
	}

	if (filter_mask & RT5645_DA_STEREO_FILTER) {
		asrc2_mask |= RT5645_DA_STO_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_STO_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_STO_CLK_SEL_SFT);
	}

	if (filter_mask & RT5645_DA_MONO_L_FILTER) {
		asrc2_mask |= RT5645_DA_MONOL_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_MONOL_CLK_SEL_SFT);
	}

	if (filter_mask & RT5645_DA_MONO_R_FILTER) {
		asrc2_mask |= RT5645_DA_MONOR_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_DA_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5645_DA_MONOR_CLK_SEL_SFT);
	}

	if (filter_mask & RT5645_AD_STEREO_FILTER) {
		asrc2_mask |= RT5645_AD_STO1_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5645_AD_STO1_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_STO1_CLK_SEL_SFT);
	}

	if (filter_mask & RT5645_AD_MONO_L_FILTER) {
		asrc3_mask |= RT5645_AD_MONOL_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5645_AD_MONOL_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_MONOL_CLK_SEL_SFT);
	}

	if (filter_mask & RT5645_AD_MONO_R_FILTER)  {
		asrc3_mask |= RT5645_AD_MONOR_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5645_AD_MONOR_CLK_SEL_MASK)
			| (clk_src << RT5645_AD_MONOR_CLK_SEL_SFT);
	}

	if (asrc2_mask)
		snd_soc_component_update_bits(component, RT5645_ASRC_2,
			asrc2_mask, asrc2_value);

	if (asrc3_mask)
		snd_soc_component_update_bits(component, RT5645_ASRC_3,
			asrc3_mask, asrc3_value);

	return 0;
}