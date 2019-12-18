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
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8994_AIF1DAC1_MUTE ; 
 int WM8994_AIF1_DAC1_FILTERS_1 ; 
 int WM8994_AIF2_DAC_FILTERS_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 

__attribute__((used)) static int wm8994_aif_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	int mute_reg;
	int reg;

	switch (codec_dai->id) {
	case 1:
		mute_reg = WM8994_AIF1_DAC1_FILTERS_1;
		break;
	case 2:
		mute_reg = WM8994_AIF2_DAC_FILTERS_1;
		break;
	default:
		return -EINVAL;
	}

	if (mute)
		reg = WM8994_AIF1DAC1_MUTE;
	else
		reg = 0;

	snd_soc_component_update_bits(component, mute_reg, WM8994_AIF1DAC1_MUTE, reg);

	return 0;
}