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
struct emu10k1x_midi {int midi_mode; int /*<<< orphan*/  tx_enable; int /*<<< orphan*/  output_lock; struct emu10k1x* emu; } ;
struct emu10k1x {int dummy; } ;
struct TYPE_2__ {struct emu10k1x_midi* private_data; } ;

/* Variables and functions */
 int EMU10K1X_MIDI_MODE_OUTPUT ; 
 scalar_t__ mpu401_output_ready (struct emu10k1x*,struct emu10k1x_midi*) ; 
 int /*<<< orphan*/  mpu401_write_data (struct emu10k1x*,struct emu10k1x_midi*,unsigned char) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emu10k1x_intr_disable (struct emu10k1x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_intr_enable (struct emu10k1x*,int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_emu10k1x_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct emu10k1x *emu;
	struct emu10k1x_midi *midi = substream->rmidi->private_data;
	unsigned long flags;

	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		return;

	if (up) {
		int max = 4;
		unsigned char byte;
	
		/* try to send some amount of bytes here before interrupts */
		spin_lock_irqsave(&midi->output_lock, flags);
		while (max > 0) {
			if (mpu401_output_ready(emu, midi)) {
				if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT) ||
				    snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					/* no more data */
					spin_unlock_irqrestore(&midi->output_lock, flags);
					return;
				}
				mpu401_write_data(emu, midi, byte);
				max--;
			} else {
				break;
			}
		}
		spin_unlock_irqrestore(&midi->output_lock, flags);
		snd_emu10k1x_intr_enable(emu, midi->tx_enable);
	} else {
		snd_emu10k1x_intr_disable(emu, midi->tx_enable);
	}
}