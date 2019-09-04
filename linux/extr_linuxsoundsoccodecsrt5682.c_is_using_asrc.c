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
#define  RT5682_ADC_STO1_ASRC_SFT 131 
#define  RT5682_CLK_SEL_I2S1_ASRC 130 
#define  RT5682_CLK_SEL_I2S2_ASRC 129 
#define  RT5682_DAC_STO1_ASRC_SFT 128 
 unsigned int RT5682_FILTER_CLK_SEL_SFT ; 
 unsigned int RT5682_PLL_TRACK_2 ; 
 unsigned int RT5682_PLL_TRACK_3 ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_using_asrc(struct snd_soc_dapm_widget *w,
			 struct snd_soc_dapm_widget *sink)
{
	unsigned int reg, shift, val;
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	switch (w->shift) {
	case RT5682_ADC_STO1_ASRC_SFT:
		reg = RT5682_PLL_TRACK_3;
		shift = RT5682_FILTER_CLK_SEL_SFT;
		break;
	case RT5682_DAC_STO1_ASRC_SFT:
		reg = RT5682_PLL_TRACK_2;
		shift = RT5682_FILTER_CLK_SEL_SFT;
		break;
	default:
		return 0;
	}

	val = (snd_soc_component_read32(component, reg) >> shift) & 0xf;
	switch (val) {
	case RT5682_CLK_SEL_I2S1_ASRC:
	case RT5682_CLK_SEL_I2S2_ASRC:
		return 1;
	default:
		return 0;
	}

}