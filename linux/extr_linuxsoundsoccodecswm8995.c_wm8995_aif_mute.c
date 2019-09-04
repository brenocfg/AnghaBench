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
 int /*<<< orphan*/  WM8995_AIF1DAC1_MUTE_MASK ; 
 int WM8995_AIF1DAC1_MUTE_SHIFT ; 
 int WM8995_AIF1_DAC1_FILTERS_1 ; 
 int WM8995_AIF2_DAC_FILTERS_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8995_aif_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	int mute_reg;

	switch (dai->id) {
	case 0:
		mute_reg = WM8995_AIF1_DAC1_FILTERS_1;
		break;
	case 1:
		mute_reg = WM8995_AIF2_DAC_FILTERS_1;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, mute_reg, WM8995_AIF1DAC1_MUTE_MASK,
			    !!mute << WM8995_AIF1DAC1_MUTE_SHIFT);
	return 0;
}