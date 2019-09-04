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
struct snd_pcm_substream {scalar_t__ runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_pcm_xrun (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irqsave (struct snd_pcm_substream*,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irqrestore (struct snd_pcm_substream*,unsigned long) ; 

int snd_pcm_stop_xrun(struct snd_pcm_substream *substream)
{
	unsigned long flags;

	snd_pcm_stream_lock_irqsave(substream, flags);
	if (substream->runtime && snd_pcm_running(substream))
		__snd_pcm_xrun(substream);
	snd_pcm_stream_unlock_irqrestore(substream, flags);
	return 0;
}