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
struct tlv320dac33_priv {int /*<<< orphan*/  substream; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  dac33_calculate_times (int /*<<< orphan*/ ,struct snd_soc_component*) ; 
 int /*<<< orphan*/  dac33_disable_digital (struct snd_soc_component*) ; 
 int /*<<< orphan*/  dac33_prepare_chip (int /*<<< orphan*/ ,struct snd_soc_component*) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dac33_playback_event(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		if (likely(dac33->substream)) {
			dac33_calculate_times(dac33->substream, component);
			dac33_prepare_chip(dac33->substream, component);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		dac33_disable_digital(component);
		break;
	}
	return 0;
}