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
struct snd_sb {scalar_t__ hardware; unsigned int open; int /*<<< orphan*/  open_lock; struct snd_rawmidi_substream* midi_substream_input; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_sb* private_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SB_DSP_MIDI_UART_IRQ ; 
 scalar_t__ SB_HW_20 ; 
 unsigned int SB_OPEN_MIDI_INPUT ; 
 unsigned int SB_OPEN_MIDI_OUTPUT ; 
 unsigned int SB_OPEN_MIDI_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sbdsp_reset (struct snd_sb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8dsp_midi_input_open(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip;
	unsigned int valid_open_flags;

	chip = substream->rmidi->private_data;
	valid_open_flags = chip->hardware >= SB_HW_20
		? SB_OPEN_MIDI_OUTPUT | SB_OPEN_MIDI_OUTPUT_TRIGGER : 0;
	spin_lock_irqsave(&chip->open_lock, flags);
	if (chip->open & ~valid_open_flags) {
		spin_unlock_irqrestore(&chip->open_lock, flags);
		return -EAGAIN;
	}
	chip->open |= SB_OPEN_MIDI_INPUT;
	chip->midi_substream_input = substream;
	if (!(chip->open & SB_OPEN_MIDI_OUTPUT)) {
		spin_unlock_irqrestore(&chip->open_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
		if (chip->hardware >= SB_HW_20)
			snd_sbdsp_command(chip, SB_DSP_MIDI_UART_IRQ);
	} else {
		spin_unlock_irqrestore(&chip->open_lock, flags);
	}
	return 0;
}