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
struct snd_rawmidi_substream {int /*<<< orphan*/  opened; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBADFD ; 
 int __snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int __snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_rawmidi_transmit(struct snd_rawmidi_substream *substream,
			 unsigned char *buffer, int count)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	int result;
	unsigned long flags;

	spin_lock_irqsave(&runtime->lock, flags);
	if (!substream->opened)
		result = -EBADFD;
	else {
		count = __snd_rawmidi_transmit_peek(substream, buffer, count);
		if (count <= 0)
			result = count;
		else
			result = __snd_rawmidi_transmit_ack(substream, count);
	}
	spin_unlock_irqrestore(&runtime->lock, flags);
	return result;
}