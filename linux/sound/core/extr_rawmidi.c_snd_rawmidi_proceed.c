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
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {scalar_t__ avail; scalar_t__ buffer_size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_rawmidi_proceed(struct snd_rawmidi_substream *substream)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	unsigned long flags;
	int count = 0;

	spin_lock_irqsave(&runtime->lock, flags);
	if (runtime->avail < runtime->buffer_size) {
		count = runtime->buffer_size - runtime->avail;
		__snd_rawmidi_transmit_ack(substream, count);
	}
	spin_unlock_irqrestore(&runtime->lock, flags);
	return count;
}