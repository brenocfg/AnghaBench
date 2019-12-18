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
struct snd_rawmidi_substream {size_t number; TYPE_1__* rmidi; } ;
struct snd_ff {int /*<<< orphan*/  lock; int /*<<< orphan*/ * rx_midi_work; int /*<<< orphan*/ * rx_midi_error; } ;
struct TYPE_2__ {struct snd_ff* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void midi_playback_trigger(struct snd_rawmidi_substream *substream,
				  int up)
{
	struct snd_ff *ff = substream->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&ff->lock, flags);

	if (up || !ff->rx_midi_error[substream->number])
		schedule_work(&ff->rx_midi_work[substream->number]);

	spin_unlock_irqrestore(&ff->lock, flags);
}