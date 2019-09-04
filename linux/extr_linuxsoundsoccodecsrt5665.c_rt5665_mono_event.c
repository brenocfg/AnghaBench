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
 int /*<<< orphan*/  RT5665_MONO_AMP_CALIB_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_MONO_NG2_CTRL_1 ; 
 int /*<<< orphan*/  RT5665_MONO_OUT ; 
 int RT5665_NG2_DIS ; 
 int RT5665_NG2_EN ; 
 int RT5665_NG2_EN_MASK ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5665_mono_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_EN);
		snd_soc_component_update_bits(component, RT5665_MONO_AMP_CALIB_CTRL_1, 0x40,
			0x0);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x10, 0x10);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x20, 0x20);
		break;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x20, 0);
		snd_soc_component_update_bits(component, RT5665_MONO_OUT, 0x10, 0);
		snd_soc_component_update_bits(component, RT5665_MONO_AMP_CALIB_CTRL_1, 0x40,
			0x40);
		snd_soc_component_update_bits(component, RT5665_MONO_NG2_CTRL_1,
			RT5665_NG2_EN_MASK, RT5665_NG2_DIS);
		break;

	default:
		return 0;
	}

	return 0;

}