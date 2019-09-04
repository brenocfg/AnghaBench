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
struct aic3x_priv {int micbias_vg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICBIAS_CTRL ; 
 int /*<<< orphan*/  MICBIAS_LEVEL_MASK ; 
 int MICBIAS_LEVEL_SHIFT ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mic_bias_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* change mic bias voltage to user defined */
		snd_soc_component_update_bits(component, MICBIAS_CTRL,
				MICBIAS_LEVEL_MASK,
				aic3x->micbias_vg << MICBIAS_LEVEL_SHIFT);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, MICBIAS_CTRL,
				MICBIAS_LEVEL_MASK, 0);
		break;
	}
	return 0;
}