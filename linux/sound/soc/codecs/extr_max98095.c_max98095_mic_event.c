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
struct snd_soc_dapm_widget {int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct max98095_priv {int /*<<< orphan*/  mic2pre; int /*<<< orphan*/  mic1pre; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M98095_05F_LVL_MIC1 ; 
 int /*<<< orphan*/  M98095_MICPRE_MASK ; 
 int M98095_MICPRE_SHIFT ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98095_mic_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (w->reg == M98095_05F_LVL_MIC1) {
			snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK,
				(1+max98095->mic1pre)<<M98095_MICPRE_SHIFT);
		} else {
			snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK,
				(1+max98095->mic2pre)<<M98095_MICPRE_SHIFT);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg, M98095_MICPRE_MASK, 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}