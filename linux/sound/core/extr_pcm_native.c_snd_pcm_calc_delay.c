#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_3__ {scalar_t__ delay; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ snd_pcm_capture_avail (TYPE_1__*) ; 
 scalar_t__ snd_pcm_playback_hw_avail (TYPE_1__*) ; 

__attribute__((used)) static inline snd_pcm_uframes_t
snd_pcm_calc_delay(struct snd_pcm_substream *substream)
{
	snd_pcm_uframes_t delay;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay = snd_pcm_playback_hw_avail(substream->runtime);
	else
		delay = snd_pcm_capture_avail(substream->runtime);
	return delay + substream->runtime->delay;
}