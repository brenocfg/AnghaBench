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
typedef  int /*<<< orphan*/  const u16 ;
struct snd_soc_component {int dummy; } ;
struct sgtl5000_priv {void** mute_state; } ;

/* Variables and functions */
#define  SGTL5000_HP_MUTE 133 
#define  SGTL5000_OUTPUTS_MUTE 132 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 void* mute_output (struct snd_soc_component*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  restore_output (struct snd_soc_component*,int /*<<< orphan*/  const,void*) ; 
 struct sgtl5000_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  vag_power_off (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  vag_power_on (struct snd_soc_component*,int) ; 

__attribute__((used)) static int vag_and_mute_control(struct snd_soc_component *component,
				 int event, int event_source)
{
	static const u16 mute_mask[] = {
		/*
		 * Mask for HP_POWER_EVENT.
		 * Muxing Headphones have to be wrapped with mute/unmute
		 * headphones only.
		 */
		SGTL5000_HP_MUTE,
		/*
		 * Masks for DAC_POWER_EVENT/ADC_POWER_EVENT.
		 * Muxing DAC or ADC block have to wrapped with mute/unmute
		 * both headphones and line-out.
		 */
		SGTL5000_OUTPUTS_MUTE,
		SGTL5000_OUTPUTS_MUTE
	};

	struct sgtl5000_priv *sgtl5000 =
		snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		sgtl5000->mute_state[event_source] =
			mute_output(component, mute_mask[event_source]);
		break;
	case SND_SOC_DAPM_POST_PMU:
		vag_power_on(component, event_source);
		restore_output(component, mute_mask[event_source],
			       sgtl5000->mute_state[event_source]);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		sgtl5000->mute_state[event_source] =
			mute_output(component, mute_mask[event_source]);
		vag_power_off(component, event_source);
		break;
	case SND_SOC_DAPM_POST_PMD:
		restore_output(component, mute_mask[event_source],
			       sgtl5000->mute_state[event_source]);
		break;
	default:
		break;
	}

	return 0;
}