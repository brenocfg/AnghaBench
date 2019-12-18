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
struct snd_pcm_runtime {scalar_t__ hw_ptr_wrap; TYPE_1__* status; int /*<<< orphan*/  buffer_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_ptr; } ;

/* Variables and functions */
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irqsave (struct snd_pcm_substream*,unsigned long) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irqrestore (struct snd_pcm_substream*,unsigned long) ; 
 scalar_t__ snd_pcm_update_hw_ptr (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_lib_ioctl_reset(struct snd_pcm_substream *substream,
				   void *arg)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long flags;
	snd_pcm_stream_lock_irqsave(substream, flags);
	if (snd_pcm_running(substream) &&
	    snd_pcm_update_hw_ptr(substream) >= 0)
		runtime->status->hw_ptr %= runtime->buffer_size;
	else {
		runtime->status->hw_ptr = 0;
		runtime->hw_ptr_wrap = 0;
	}
	snd_pcm_stream_unlock_irqrestore(substream, flags);
	return 0;
}