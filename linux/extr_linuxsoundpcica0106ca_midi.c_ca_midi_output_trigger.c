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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_ca_midi {int midi_mode; int /*<<< orphan*/  tx_enable; int /*<<< orphan*/  (* interrupt_disable ) (struct snd_ca_midi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* interrupt_enable ) (struct snd_ca_midi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  output_lock; int /*<<< orphan*/  dev_id; } ;
struct TYPE_2__ {struct snd_ca_midi* private_data; } ;

/* Variables and functions */
 int CA_MIDI_MODE_OUTPUT ; 
 scalar_t__ ca_midi_output_ready (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  ca_midi_write_data (struct snd_ca_midi*,unsigned char) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_ca_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_ca_midi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_ca_midi *midi = substream->rmidi->private_data;
	unsigned long flags;

	if (snd_BUG_ON(!midi->dev_id))
		return;

	if (up) {
		int max = 4;
		unsigned char byte;

		spin_lock_irqsave(&midi->output_lock, flags);
	
		/* try to send some amount of bytes here before interrupts */
		while (max > 0) {
			if (ca_midi_output_ready(midi)) {
				if (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT) ||
				    snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					/* no more data */
					spin_unlock_irqrestore(&midi->output_lock, flags);
					return;
				}
				ca_midi_write_data(midi, byte);
				max--;
			} else {
				break;
			}
		}

		spin_unlock_irqrestore(&midi->output_lock, flags);
		midi->interrupt_enable(midi,midi->tx_enable);

	} else {
		midi->interrupt_disable(midi,midi->tx_enable);
	}
}