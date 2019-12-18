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
 unsigned int RT5682_AD_STEREO1_FILTER ; 
#define  RT5682_CLK_SEL_I2S1_ASRC 130 
#define  RT5682_CLK_SEL_I2S2_ASRC 129 
#define  RT5682_CLK_SEL_SYS 128 
 unsigned int RT5682_DA_STEREO1_FILTER ; 
 int /*<<< orphan*/  RT5682_FILTER_CLK_SEL_MASK ; 
 unsigned int RT5682_FILTER_CLK_SEL_SFT ; 
 int /*<<< orphan*/  RT5682_PLL_TRACK_2 ; 
 int /*<<< orphan*/  RT5682_PLL_TRACK_3 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int rt5682_sel_asrc_clk_src(struct snd_soc_component *component,
		unsigned int filter_mask, unsigned int clk_src)
{

	switch (clk_src) {
	case RT5682_CLK_SEL_SYS:
	case RT5682_CLK_SEL_I2S1_ASRC:
	case RT5682_CLK_SEL_I2S2_ASRC:
		break;

	default:
		return -EINVAL;
	}

	if (filter_mask & RT5682_DA_STEREO1_FILTER) {
		snd_soc_component_update_bits(component, RT5682_PLL_TRACK_2,
			RT5682_FILTER_CLK_SEL_MASK,
			clk_src << RT5682_FILTER_CLK_SEL_SFT);
	}

	if (filter_mask & RT5682_AD_STEREO1_FILTER) {
		snd_soc_component_update_bits(component, RT5682_PLL_TRACK_3,
			RT5682_FILTER_CLK_SEL_MASK,
			clk_src << RT5682_FILTER_CLK_SEL_SFT);
	}

	return 0;
}