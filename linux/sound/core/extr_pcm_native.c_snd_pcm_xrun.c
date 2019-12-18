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
struct snd_pcm_runtime {TYPE_1__* status; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int EBADFD ; 
#define  SNDRV_PCM_STATE_RUNNING 129 
#define  SNDRV_PCM_STATE_XRUN 128 
 int /*<<< orphan*/  __snd_pcm_xrun (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_xrun(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int result;

	snd_pcm_stream_lock_irq(substream);
	switch (runtime->status->state) {
	case SNDRV_PCM_STATE_XRUN:
		result = 0;	/* already there */
		break;
	case SNDRV_PCM_STATE_RUNNING:
		__snd_pcm_xrun(substream);
		result = 0;
		break;
	default:
		result = -EBADFD;
	}
	snd_pcm_stream_unlock_irq(substream);
	return result;
}