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
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_pcm_capture_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_playback_avail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline snd_pcm_uframes_t
snd_pcm_avail(struct snd_pcm_substream *substream)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return snd_pcm_playback_avail(substream->runtime);
	else
		return snd_pcm_capture_avail(substream->runtime);
}