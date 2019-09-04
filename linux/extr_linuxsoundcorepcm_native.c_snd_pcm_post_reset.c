#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ silence_size; TYPE_2__* status; TYPE_1__* control; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  appl_ptr; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  snd_pcm_playback_silence (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_pcm_post_reset(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	runtime->control->appl_ptr = runtime->status->hw_ptr;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    runtime->silence_size > 0)
		snd_pcm_playback_silence(substream, ULONG_MAX);
}