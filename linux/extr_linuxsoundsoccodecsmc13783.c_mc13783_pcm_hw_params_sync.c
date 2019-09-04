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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int mc13783_pcm_hw_params_codec (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 
 int mc13783_pcm_hw_params_dac (struct snd_pcm_substream*,struct snd_pcm_hw_params*,struct snd_soc_dai*) ; 

__attribute__((used)) static int mc13783_pcm_hw_params_sync(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return mc13783_pcm_hw_params_dac(substream, params, dai);
	else
		return mc13783_pcm_hw_params_codec(substream, params, dai);
}