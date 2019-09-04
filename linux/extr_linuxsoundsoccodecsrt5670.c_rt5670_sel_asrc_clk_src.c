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
 unsigned int RT5670_AD_MONOL_CLK_SEL_MASK ; 
 unsigned int RT5670_AD_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5670_AD_MONOR_CLK_SEL_MASK ; 
 unsigned int RT5670_AD_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5670_AD_MONO_L_FILTER ; 
 unsigned int RT5670_AD_MONO_R_FILTER ; 
 unsigned int RT5670_AD_STEREO_FILTER ; 
 unsigned int RT5670_AD_STO1_CLK_SEL_MASK ; 
 unsigned int RT5670_AD_STO1_CLK_SEL_SFT ; 
 int /*<<< orphan*/  RT5670_ASRC_2 ; 
 int /*<<< orphan*/  RT5670_ASRC_3 ; 
 unsigned int RT5670_CLK_SEL_SYS3 ; 
 unsigned int RT5670_DA_MONOL_CLK_SEL_MASK ; 
 unsigned int RT5670_DA_MONOL_CLK_SEL_SFT ; 
 unsigned int RT5670_DA_MONOR_CLK_SEL_MASK ; 
 unsigned int RT5670_DA_MONOR_CLK_SEL_SFT ; 
 unsigned int RT5670_DA_MONO_L_FILTER ; 
 unsigned int RT5670_DA_MONO_R_FILTER ; 
 unsigned int RT5670_DA_STEREO_FILTER ; 
 unsigned int RT5670_DA_STO_CLK_SEL_MASK ; 
 unsigned int RT5670_DA_STO_CLK_SEL_SFT ; 
 unsigned int RT5670_DOWN_CLK_SEL_MASK ; 
 unsigned int RT5670_DOWN_CLK_SEL_SFT ; 
 unsigned int RT5670_DOWN_RATE_FILTER ; 
 unsigned int RT5670_UP_CLK_SEL_MASK ; 
 unsigned int RT5670_UP_CLK_SEL_SFT ; 
 unsigned int RT5670_UP_RATE_FILTER ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int rt5670_sel_asrc_clk_src(struct snd_soc_component *component,
			    unsigned int filter_mask, unsigned int clk_src)
{
	unsigned int asrc2_mask = 0, asrc2_value = 0;
	unsigned int asrc3_mask = 0, asrc3_value = 0;

	if (clk_src > RT5670_CLK_SEL_SYS3)
		return -EINVAL;

	if (filter_mask & RT5670_DA_STEREO_FILTER) {
		asrc2_mask |= RT5670_DA_STO_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_STO_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_STO_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_DA_MONO_L_FILTER) {
		asrc2_mask |= RT5670_DA_MONOL_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_MONOL_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_MONOL_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_DA_MONO_R_FILTER) {
		asrc2_mask |= RT5670_DA_MONOR_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_DA_MONOR_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DA_MONOR_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_AD_STEREO_FILTER) {
		asrc2_mask |= RT5670_AD_STO1_CLK_SEL_MASK;
		asrc2_value = (asrc2_value & ~RT5670_AD_STO1_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_STO1_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_AD_MONO_L_FILTER) {
		asrc3_mask |= RT5670_AD_MONOL_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_AD_MONOL_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_MONOL_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_AD_MONO_R_FILTER)  {
		asrc3_mask |= RT5670_AD_MONOR_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_AD_MONOR_CLK_SEL_MASK)
				| (clk_src <<  RT5670_AD_MONOR_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_UP_RATE_FILTER) {
		asrc3_mask |= RT5670_UP_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_UP_CLK_SEL_MASK)
				| (clk_src <<  RT5670_UP_CLK_SEL_SFT);
	}

	if (filter_mask & RT5670_DOWN_RATE_FILTER) {
		asrc3_mask |= RT5670_DOWN_CLK_SEL_MASK;
		asrc3_value = (asrc3_value & ~RT5670_DOWN_CLK_SEL_MASK)
				| (clk_src <<  RT5670_DOWN_CLK_SEL_SFT);
	}

	if (asrc2_mask)
		snd_soc_component_update_bits(component, RT5670_ASRC_2,
				    asrc2_mask, asrc2_value);

	if (asrc3_mask)
		snd_soc_component_update_bits(component, RT5670_ASRC_3,
				    asrc3_mask, asrc3_value);
	return 0;
}