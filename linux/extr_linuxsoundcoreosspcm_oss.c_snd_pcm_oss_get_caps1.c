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
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int DSP_CAP_DUPLEX ; 

__attribute__((used)) static int snd_pcm_oss_get_caps1(struct snd_pcm_substream *substream, int res)
{

	if (substream == NULL) {
		res &= ~DSP_CAP_DUPLEX;
		return res;
	}
#ifdef DSP_CAP_MULTI
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		if (substream->pstr->substream_count > 1)
			res |= DSP_CAP_MULTI;
#endif
	/* DSP_CAP_REALTIME is set all times: */
	/* all ALSA drivers can return actual pointer in ring buffer */
#if defined(DSP_CAP_REALTIME) && 0
	{
		struct snd_pcm_runtime *runtime = substream->runtime;
		if (runtime->info & (SNDRV_PCM_INFO_BLOCK_TRANSFER|SNDRV_PCM_INFO_BATCH))
			res &= ~DSP_CAP_REALTIME;
	}
#endif
	return res;
}