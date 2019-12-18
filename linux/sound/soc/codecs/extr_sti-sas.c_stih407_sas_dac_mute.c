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
 int /*<<< orphan*/  STIH407_AUDIO_DAC_CTRL ; 
 int /*<<< orphan*/  STIH407_DAC_SOFTMUTE_MASK ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stih407_sas_dac_mute(struct snd_soc_dai *dai, int mute, int stream)
{
	struct snd_soc_component *component = dai->component;

	if (mute) {
		return snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					    STIH407_DAC_SOFTMUTE_MASK,
					    STIH407_DAC_SOFTMUTE_MASK);
	} else {
		return snd_soc_component_update_bits(component, STIH407_AUDIO_DAC_CTRL,
					    STIH407_DAC_SOFTMUTE_MASK,
					    0);
	}
}