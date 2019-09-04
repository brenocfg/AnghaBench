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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MC13783_AUDIO_DAC ; 
 unsigned int* mc13783_rates ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mc13783_pcm_hw_params_dac(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned int rate = params_rate(params);
	int i;

	for (i = 0; i < ARRAY_SIZE(mc13783_rates); i++) {
		if (rate == mc13783_rates[i]) {
			snd_soc_component_update_bits(component, MC13783_AUDIO_DAC,
					0xf << 17, i << 17);
			return 0;
		}
	}

	return -EINVAL;
}