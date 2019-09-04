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
struct snd_pcm_substream {int f_flags; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EBUSY ; 
 scalar_t__ SNDRV_PCM_STATE_DISCONNECTED ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_pre_prepare(struct snd_pcm_substream *substream,
			       int f_flags)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->status->state == SNDRV_PCM_STATE_OPEN ||
	    runtime->status->state == SNDRV_PCM_STATE_DISCONNECTED)
		return -EBADFD;
	if (snd_pcm_running(substream))
		return -EBUSY;
	substream->f_flags = f_flags;
	return 0;
}