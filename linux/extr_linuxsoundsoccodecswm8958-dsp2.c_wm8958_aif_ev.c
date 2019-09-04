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
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_dsp_apply (struct snd_soc_component*,int,int) ; 

int wm8958_aif_ev(struct snd_soc_dapm_widget *w,
		  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	int i;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
	case SND_SOC_DAPM_PRE_PMU:
		for (i = 0; i < 3; i++)
			wm8958_dsp_apply(component, i, 1);
		break;
	case SND_SOC_DAPM_POST_PMD:
	case SND_SOC_DAPM_PRE_PMD:
		for (i = 0; i < 3; i++)
			wm8958_dsp_apply(component, i, 0);
		break;
	}

	return 0;
}