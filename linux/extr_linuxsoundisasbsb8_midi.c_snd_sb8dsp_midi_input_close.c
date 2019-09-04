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
struct snd_sb {int open; int /*<<< orphan*/  open_lock; int /*<<< orphan*/ * midi_substream_input; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_sb* private_data; } ;

/* Variables and functions */
 int SB_OPEN_MIDI_INPUT ; 
 int SB_OPEN_MIDI_INPUT_TRIGGER ; 
 int SB_OPEN_MIDI_OUTPUT ; 
 int /*<<< orphan*/  snd_sbdsp_reset (struct snd_sb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8dsp_midi_input_close(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip;

	chip = substream->rmidi->private_data;
	spin_lock_irqsave(&chip->open_lock, flags);
	chip->open &= ~(SB_OPEN_MIDI_INPUT | SB_OPEN_MIDI_INPUT_TRIGGER);
	chip->midi_substream_input = NULL;
	if (!(chip->open & SB_OPEN_MIDI_OUTPUT)) {
		spin_unlock_irqrestore(&chip->open_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
	} else {
		spin_unlock_irqrestore(&chip->open_lock, flags);
	}
	return 0;
}