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
struct snd_pcm_runtime {struct snd_pcm_substream* trigger_master; TYPE_1__* status; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int EBADFD ; 
#define  SNDRV_PCM_STATE_DISCONNECTED 130 
#define  SNDRV_PCM_STATE_OPEN 129 
#define  SNDRV_PCM_STATE_SUSPENDED 128 

__attribute__((used)) static int snd_pcm_pre_drain_init(struct snd_pcm_substream *substream, int state)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_OPEN:
	case SNDRV_PCM_STATE_DISCONNECTED:
	case SNDRV_PCM_STATE_SUSPENDED:
		return -EBADFD;
	}
	runtime->trigger_master = substream;
	return 0;
}