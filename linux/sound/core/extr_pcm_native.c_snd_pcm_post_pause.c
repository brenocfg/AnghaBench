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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; int /*<<< orphan*/  tsleep; int /*<<< orphan*/  sleep; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_PAUSED ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_RUNNING ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_MCONTINUE ; 
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_MPAUSE ; 
 int /*<<< orphan*/  snd_pcm_timer_notify (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_trigger_tstamp (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_pcm_post_pause(struct snd_pcm_substream *substream, int push)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_trigger_tstamp(substream);
	if (push) {
		runtime->status->state = SNDRV_PCM_STATE_PAUSED;
		snd_pcm_timer_notify(substream, SNDRV_TIMER_EVENT_MPAUSE);
		wake_up(&runtime->sleep);
		wake_up(&runtime->tsleep);
	} else {
		runtime->status->state = SNDRV_PCM_STATE_RUNNING;
		snd_pcm_timer_notify(substream, SNDRV_TIMER_EVENT_MCONTINUE);
	}
}