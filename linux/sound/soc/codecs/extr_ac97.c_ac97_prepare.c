#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int AC97_PCM_FRONT_DAC_RATE ; 
 int AC97_PCM_LR_ADC_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_ac97_set_rate (struct snd_ac97*,int,int /*<<< orphan*/ ) ; 
 struct snd_ac97* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ac97_prepare(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	int reg = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		  AC97_PCM_FRONT_DAC_RATE : AC97_PCM_LR_ADC_RATE;
	return snd_ac97_set_rate(ac97, reg, substream->runtime->rate);
}