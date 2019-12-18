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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  pxa2xx_ac97_pcm_mic_mono_in ; 
 int /*<<< orphan*/  snd_soc_dai_set_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa2xx_ac97_mic_startup(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *cpu_dai)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return -ENODEV;
	snd_soc_dai_set_dma_data(cpu_dai, substream,
				 &pxa2xx_ac97_pcm_mic_mono_in);

	return 0;
}