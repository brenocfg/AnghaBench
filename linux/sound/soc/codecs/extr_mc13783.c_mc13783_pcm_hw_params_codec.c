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
 unsigned int AUDIO_CODEC_CDCFS8K16K ; 
 int EINVAL ; 
 int /*<<< orphan*/  MC13783_AUDIO_CODEC ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int mc13783_pcm_hw_params_codec(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned int rate = params_rate(params);
	unsigned int val;

	switch (rate) {
	case 8000:
		val = 0;
		break;
	case 16000:
		val = AUDIO_CODEC_CDCFS8K16K;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, MC13783_AUDIO_CODEC, AUDIO_CODEC_CDCFS8K16K,
			val);

	return 0;
}