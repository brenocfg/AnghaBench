#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; TYPE_3__* ops; struct snd_pcm_runtime* runtime; } ;
struct TYPE_5__ {int info; } ;
struct snd_pcm_runtime {TYPE_2__ hw; struct snd_pcm_substream* trigger_master; TYPE_1__* status; } ;
struct TYPE_6__ {int (* trigger ) (struct snd_pcm_substream*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int state; } ;

/* Variables and functions */
 int SNDRV_PCM_INFO_DRAIN_TRIGGER ; 
 void* SNDRV_PCM_STATE_DRAINING ; 
#define  SNDRV_PCM_STATE_PREPARED 130 
#define  SNDRV_PCM_STATE_RUNNING 129 
 void* SNDRV_PCM_STATE_SETUP ; 
#define  SNDRV_PCM_STATE_XRUN 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_DRAIN ; 
 scalar_t__ snd_pcm_capture_avail (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_do_start (struct snd_pcm_substream*,void*) ; 
 int /*<<< orphan*/  snd_pcm_do_stop (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_playback_empty (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_post_start (struct snd_pcm_substream*,void*) ; 
 int /*<<< orphan*/  snd_pcm_post_stop (struct snd_pcm_substream*,int) ; 
 int stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_do_drain_init(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (runtime->status->state) {
		case SNDRV_PCM_STATE_PREPARED:
			/* start playback stream if possible */
			if (! snd_pcm_playback_empty(substream)) {
				snd_pcm_do_start(substream, SNDRV_PCM_STATE_DRAINING);
				snd_pcm_post_start(substream, SNDRV_PCM_STATE_DRAINING);
			} else {
				runtime->status->state = SNDRV_PCM_STATE_SETUP;
			}
			break;
		case SNDRV_PCM_STATE_RUNNING:
			runtime->status->state = SNDRV_PCM_STATE_DRAINING;
			break;
		case SNDRV_PCM_STATE_XRUN:
			runtime->status->state = SNDRV_PCM_STATE_SETUP;
			break;
		default:
			break;
		}
	} else {
		/* stop running stream */
		if (runtime->status->state == SNDRV_PCM_STATE_RUNNING) {
			int new_state = snd_pcm_capture_avail(runtime) > 0 ?
				SNDRV_PCM_STATE_DRAINING : SNDRV_PCM_STATE_SETUP;
			snd_pcm_do_stop(substream, new_state);
			snd_pcm_post_stop(substream, new_state);
		}
	}

	if (runtime->status->state == SNDRV_PCM_STATE_DRAINING &&
	    runtime->trigger_master == substream &&
	    (runtime->hw.info & SNDRV_PCM_INFO_DRAIN_TRIGGER))
		return substream->ops->trigger(substream,
					       SNDRV_PCM_TRIGGER_DRAIN);

	return 0;
}