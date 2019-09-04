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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_runtime {scalar_t__ avail_max; scalar_t__ buffer_size; scalar_t__ stop_threshold; scalar_t__ twake; int /*<<< orphan*/  sleep; TYPE_1__* control; int /*<<< orphan*/  tsleep; TYPE_2__* status; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {scalar_t__ avail_min; } ;

/* Variables and functions */
 int EPIPE ; 
 scalar_t__ SNDRV_PCM_STATE_DRAINING ; 
 int /*<<< orphan*/  __snd_pcm_xrun (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_avail (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_drain_done (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int snd_pcm_update_state(struct snd_pcm_substream *substream,
			 struct snd_pcm_runtime *runtime)
{
	snd_pcm_uframes_t avail;

	avail = snd_pcm_avail(substream);
	if (avail > runtime->avail_max)
		runtime->avail_max = avail;
	if (runtime->status->state == SNDRV_PCM_STATE_DRAINING) {
		if (avail >= runtime->buffer_size) {
			snd_pcm_drain_done(substream);
			return -EPIPE;
		}
	} else {
		if (avail >= runtime->stop_threshold) {
			__snd_pcm_xrun(substream);
			return -EPIPE;
		}
	}
	if (runtime->twake) {
		if (avail >= runtime->twake)
			wake_up(&runtime->tsleep);
	} else if (avail >= runtime->control->avail_min)
		wake_up(&runtime->sleep);
	return 0;
}