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
 int /*<<< orphan*/  CS4265_DAC_CTL ; 
 int /*<<< orphan*/  CS4265_DAC_CTL_MUTE ; 
 int /*<<< orphan*/  CS4265_SPDIF_CTL2 ; 
 int /*<<< orphan*/  CS4265_SPDIF_CTL2_MUTE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4265_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;

	if (mute) {
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_MUTE,
			CS4265_DAC_CTL_MUTE);
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_MUTE,
			CS4265_SPDIF_CTL2_MUTE);
	} else {
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_MUTE,
			0);
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_MUTE,
			0);
	}
	return 0;
}