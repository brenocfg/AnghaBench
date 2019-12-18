#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  timer; scalar_t__ timer_running; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  fasync; } ;

/* Variables and functions */
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irqsave (struct snd_pcm_substream*,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irqrestore (struct snd_pcm_substream*,unsigned long) ; 
 scalar_t__ snd_pcm_update_hw_ptr0 (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_timer_interrupt (int /*<<< orphan*/ ,int) ; 

void snd_pcm_period_elapsed(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	unsigned long flags;

	if (PCM_RUNTIME_CHECK(substream))
		return;
	runtime = substream->runtime;

	snd_pcm_stream_lock_irqsave(substream, flags);
	if (!snd_pcm_running(substream) ||
	    snd_pcm_update_hw_ptr0(substream, 1) < 0)
		goto _end;

#ifdef CONFIG_SND_PCM_TIMER
	if (substream->timer_running)
		snd_timer_interrupt(substream->timer, 1);
#endif
 _end:
	kill_fasync(&runtime->fasync, SIGIO, POLL_IN);
	snd_pcm_stream_unlock_irqrestore(substream, flags);
}