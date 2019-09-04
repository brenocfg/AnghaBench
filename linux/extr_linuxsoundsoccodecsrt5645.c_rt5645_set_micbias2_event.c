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

/* Variables and functions */
 int /*<<< orphan*/  RT5645_GEN_CTRL2 ; 
 int /*<<< orphan*/  RT5645_MICBIAS2_POW_CTRL_SEL_A ; 
 int /*<<< orphan*/  RT5645_MICBIAS2_POW_CTRL_SEL_M ; 
 int /*<<< orphan*/  RT5645_MICBIAS2_POW_CTRL_SEL_MASK ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5645_set_micbias2_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *k, int  event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS2_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS2_POW_CTRL_SEL_M);
		break;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5645_GEN_CTRL2,
			RT5645_MICBIAS2_POW_CTRL_SEL_MASK,
			RT5645_MICBIAS2_POW_CTRL_SEL_A);
		break;

	default:
		return 0;
	}

	return 0;
}