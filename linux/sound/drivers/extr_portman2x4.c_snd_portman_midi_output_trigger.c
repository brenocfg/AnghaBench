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
struct snd_rawmidi_substream {int /*<<< orphan*/  number; TYPE_1__* rmidi; } ;
struct portman {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct portman* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  portman_write_midi (struct portman*,int /*<<< orphan*/ ,unsigned char) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_portman_midi_output_trigger(struct snd_rawmidi_substream *substream,
					    int up)
{
	struct portman *pm = substream->rmidi->private_data;
	unsigned long flags;
	unsigned char byte;

	spin_lock_irqsave(&pm->reg_lock, flags);
	if (up) {
		while ((snd_rawmidi_transmit(substream, &byte, 1) == 1))
			portman_write_midi(pm, substream->number, byte);
	}
	spin_unlock_irqrestore(&pm->reg_lock, flags);
}