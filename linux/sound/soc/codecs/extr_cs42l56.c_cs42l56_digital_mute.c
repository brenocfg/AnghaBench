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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int CS42L56_ADCAMIX_MUTE_MASK ; 
 int CS42L56_ADCA_MUTE_MASK ; 
 int CS42L56_ADCBMIX_MUTE_MASK ; 
 int CS42L56_ADCB_MUTE_MASK ; 
 int /*<<< orphan*/  CS42L56_DSP_MUTE_CTL ; 
 int /*<<< orphan*/  CS42L56_HPA_VOLUME ; 
 int /*<<< orphan*/  CS42L56_HPB_VOLUME ; 
 int CS42L56_HP_MUTE_MASK ; 
 int /*<<< orphan*/  CS42L56_LOA_VOLUME ; 
 int /*<<< orphan*/  CS42L56_LOB_VOLUME ; 
 int CS42L56_LO_MUTE_MASK ; 
 int /*<<< orphan*/  CS42L56_MISC_ADC_CTL ; 
 int CS42L56_MSTA_MUTE_MASK ; 
 int CS42L56_MSTB_MUTE_MASK ; 
 int /*<<< orphan*/  CS42L56_MUTE_ALL ; 
 int CS42L56_PCMAMIX_MUTE_MASK ; 
 int CS42L56_PCMBMIX_MUTE_MASK ; 
 int /*<<< orphan*/  CS42L56_UNMUTE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l56_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;

	if (mute) {
		/* Hit the DSP Mixer first */
		snd_soc_component_update_bits(component, CS42L56_DSP_MUTE_CTL,
				    CS42L56_ADCAMIX_MUTE_MASK |
				    CS42L56_ADCBMIX_MUTE_MASK |
				    CS42L56_PCMAMIX_MUTE_MASK |
				    CS42L56_PCMBMIX_MUTE_MASK |
				    CS42L56_MSTB_MUTE_MASK |
				    CS42L56_MSTA_MUTE_MASK,
				    CS42L56_MUTE_ALL);
		/* Mute ADC's */
		snd_soc_component_update_bits(component, CS42L56_MISC_ADC_CTL,
				    CS42L56_ADCA_MUTE_MASK |
				    CS42L56_ADCB_MUTE_MASK,
				    CS42L56_MUTE_ALL);
		/* HP And LO */
		snd_soc_component_update_bits(component, CS42L56_HPA_VOLUME,
				    CS42L56_HP_MUTE_MASK, CS42L56_MUTE_ALL);
		snd_soc_component_update_bits(component, CS42L56_HPB_VOLUME,
				    CS42L56_HP_MUTE_MASK, CS42L56_MUTE_ALL);
		snd_soc_component_update_bits(component, CS42L56_LOA_VOLUME,
				    CS42L56_LO_MUTE_MASK, CS42L56_MUTE_ALL);
		snd_soc_component_update_bits(component, CS42L56_LOB_VOLUME,
				    CS42L56_LO_MUTE_MASK, CS42L56_MUTE_ALL);
	} else {
		snd_soc_component_update_bits(component, CS42L56_DSP_MUTE_CTL,
				    CS42L56_ADCAMIX_MUTE_MASK |
				    CS42L56_ADCBMIX_MUTE_MASK |
				    CS42L56_PCMAMIX_MUTE_MASK |
				    CS42L56_PCMBMIX_MUTE_MASK |
				    CS42L56_MSTB_MUTE_MASK |
				    CS42L56_MSTA_MUTE_MASK,
				    CS42L56_UNMUTE);

		snd_soc_component_update_bits(component, CS42L56_MISC_ADC_CTL,
				    CS42L56_ADCA_MUTE_MASK |
				    CS42L56_ADCB_MUTE_MASK,
				    CS42L56_UNMUTE);

		snd_soc_component_update_bits(component, CS42L56_HPA_VOLUME,
				    CS42L56_HP_MUTE_MASK, CS42L56_UNMUTE);
		snd_soc_component_update_bits(component, CS42L56_HPB_VOLUME,
				    CS42L56_HP_MUTE_MASK, CS42L56_UNMUTE);
		snd_soc_component_update_bits(component, CS42L56_LOA_VOLUME,
				    CS42L56_LO_MUTE_MASK, CS42L56_UNMUTE);
		snd_soc_component_update_bits(component, CS42L56_LOB_VOLUME,
				    CS42L56_LO_MUTE_MASK, CS42L56_UNMUTE);
	}
	return 0;
}