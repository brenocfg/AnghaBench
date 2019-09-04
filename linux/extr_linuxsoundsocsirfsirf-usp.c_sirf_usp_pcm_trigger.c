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
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct sirf_usp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  sirf_usp_rx_disable (struct sirf_usp*) ; 
 int /*<<< orphan*/  sirf_usp_rx_enable (struct sirf_usp*) ; 
 int /*<<< orphan*/  sirf_usp_tx_disable (struct sirf_usp*) ; 
 int /*<<< orphan*/  sirf_usp_tx_enable (struct sirf_usp*) ; 
 struct sirf_usp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int sirf_usp_pcm_trigger(struct snd_pcm_substream *substream, int cmd,
				struct snd_soc_dai *dai)
{
	struct sirf_usp *usp = snd_soc_dai_get_drvdata(dai);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sirf_usp_tx_enable(usp);
		else
			sirf_usp_rx_enable(usp);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			sirf_usp_tx_disable(usp);
		else
			sirf_usp_rx_disable(usp);
		break;
	}

	return 0;
}