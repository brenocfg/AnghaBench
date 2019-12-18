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
struct snd_pcm_runtime {int info; struct snd_pcm_substream* trigger_master; TYPE_1__* status; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBADFD ; 
 int ENOSYS ; 
 int SNDRV_PCM_INFO_PAUSE ; 
 scalar_t__ SNDRV_PCM_STATE_PAUSED ; 
 scalar_t__ SNDRV_PCM_STATE_RUNNING ; 

__attribute__((used)) static int snd_pcm_pre_pause(struct snd_pcm_substream *substream, int push)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (!(runtime->info & SNDRV_PCM_INFO_PAUSE))
		return -ENOSYS;
	if (push) {
		if (runtime->status->state != SNDRV_PCM_STATE_RUNNING)
			return -EBADFD;
	} else if (runtime->status->state != SNDRV_PCM_STATE_PAUSED)
		return -EBADFD;
	runtime->trigger_master = substream;
	return 0;
}