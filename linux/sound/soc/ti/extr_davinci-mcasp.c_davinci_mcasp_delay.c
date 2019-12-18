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
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct davinci_mcasp {int dummy; } ;
typedef  int snd_pcm_sframes_t ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int davinci_mcasp_rx_delay (struct davinci_mcasp*) ; 
 int davinci_mcasp_tx_delay (struct davinci_mcasp*) ; 
 struct davinci_mcasp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static snd_pcm_sframes_t davinci_mcasp_delay(
			struct snd_pcm_substream *substream,
			struct snd_soc_dai *cpu_dai)
{
	struct davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	u32 fifo_use;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		fifo_use = davinci_mcasp_tx_delay(mcasp);
	else
		fifo_use = davinci_mcasp_rx_delay(mcasp);

	/*
	 * Divide the used locations with the channel count to get the
	 * FIFO usage in samples (don't care about partial samples in the
	 * buffer).
	 */
	return fifo_use / substream->runtime->channels;
}