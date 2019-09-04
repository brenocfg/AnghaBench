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
struct snd_sb {scalar_t__ hardware; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  midi_timer; int /*<<< orphan*/  open; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_sb* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP (struct snd_sb*,int /*<<< orphan*/ ) ; 
 char SB_DSP_MIDI_OUTPUT ; 
 scalar_t__ SB_HW_20 ; 
 int /*<<< orphan*/  SB_OPEN_MIDI_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,char*,int) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sb8dsp_midi_output_write(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip;
	char byte;
	int max = 32;

	/* how big is Tx FIFO? */
	chip = substream->rmidi->private_data;
	while (max-- > 0) {
		spin_lock_irqsave(&chip->open_lock, flags);
		if (snd_rawmidi_transmit_peek(substream, &byte, 1) != 1) {
			chip->open &= ~SB_OPEN_MIDI_OUTPUT_TRIGGER;
			del_timer(&chip->midi_timer);
			spin_unlock_irqrestore(&chip->open_lock, flags);
			break;
		}
		if (chip->hardware >= SB_HW_20) {
			int timeout = 8;
			while ((inb(SBP(chip, STATUS)) & 0x80) != 0 && --timeout > 0)
				;
			if (timeout == 0) {
				/* Tx FIFO full - try again later */
				spin_unlock_irqrestore(&chip->open_lock, flags);
				break;
			}
			outb(byte, SBP(chip, WRITE));
		} else {
			snd_sbdsp_command(chip, SB_DSP_MIDI_OUTPUT);
			snd_sbdsp_command(chip, byte);
		}
		snd_rawmidi_transmit_ack(substream, 1);
		spin_unlock_irqrestore(&chip->open_lock, flags);
	}
}