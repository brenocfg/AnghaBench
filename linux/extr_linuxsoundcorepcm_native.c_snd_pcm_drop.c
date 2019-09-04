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
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBADFD ; 
 int ENXIO ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 scalar_t__ SNDRV_PCM_STATE_DISCONNECTED ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 scalar_t__ SNDRV_PCM_STATE_PAUSED ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_SETUP ; 
 int /*<<< orphan*/  snd_pcm_pause (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_drop(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	int result = 0;
	
	if (PCM_RUNTIME_CHECK(substream))
		return -ENXIO;
	runtime = substream->runtime;

	if (runtime->status->state == SNDRV_PCM_STATE_OPEN ||
	    runtime->status->state == SNDRV_PCM_STATE_DISCONNECTED)
		return -EBADFD;

	snd_pcm_stream_lock_irq(substream);
	/* resume pause */
	if (runtime->status->state == SNDRV_PCM_STATE_PAUSED)
		snd_pcm_pause(substream, 0);

	snd_pcm_stop(substream, SNDRV_PCM_STATE_SETUP);
	/* runtime->control->appl_ptr = runtime->status->hw_ptr; */
	snd_pcm_stream_unlock_irq(substream);

	return result;
}