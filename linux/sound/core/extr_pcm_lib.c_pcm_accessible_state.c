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
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int EBADFD ; 
 int EPIPE ; 
 int ESTRPIPE ; 
#define  SNDRV_PCM_STATE_PAUSED 132 
#define  SNDRV_PCM_STATE_PREPARED 131 
#define  SNDRV_PCM_STATE_RUNNING 130 
#define  SNDRV_PCM_STATE_SUSPENDED 129 
#define  SNDRV_PCM_STATE_XRUN 128 

__attribute__((used)) static int pcm_accessible_state(struct snd_pcm_runtime *runtime)
{
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_PREPARED:
	case SNDRV_PCM_STATE_RUNNING:
	case SNDRV_PCM_STATE_PAUSED:
		return 0;
	case SNDRV_PCM_STATE_XRUN:
		return -EPIPE;
	case SNDRV_PCM_STATE_SUSPENDED:
		return -ESTRPIPE;
	default:
		return -EBADFD;
	}
}