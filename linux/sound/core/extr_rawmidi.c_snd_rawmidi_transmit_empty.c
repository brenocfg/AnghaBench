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
struct snd_rawmidi_substream {int /*<<< orphan*/  rmidi; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {scalar_t__ avail; scalar_t__ buffer_size; int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmidi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_rawmidi_transmit_empty(struct snd_rawmidi_substream *substream)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	int result;
	unsigned long flags;

	if (runtime->buffer == NULL) {
		rmidi_dbg(substream->rmidi,
			  "snd_rawmidi_transmit_empty: output is not active!!!\n");
		return 1;
	}
	spin_lock_irqsave(&runtime->lock, flags);
	result = runtime->avail >= runtime->buffer_size;
	spin_unlock_irqrestore(&runtime->lock, flags);
	return result;
}