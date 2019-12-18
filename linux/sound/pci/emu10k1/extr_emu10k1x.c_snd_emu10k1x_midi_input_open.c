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
struct emu10k1x_midi {int midi_mode; int /*<<< orphan*/  open_lock; struct snd_rawmidi_substream* substream_input; struct emu10k1x* emu; } ;
struct emu10k1x {int dummy; } ;
struct TYPE_2__ {struct emu10k1x_midi* private_data; } ;

/* Variables and functions */
 int EIO ; 
 int EMU10K1X_MIDI_MODE_INPUT ; 
 int EMU10K1X_MIDI_MODE_OUTPUT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPU401_ENTER_UART ; 
 int /*<<< orphan*/  MPU401_RESET ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_emu10k1x_midi_cmd (struct emu10k1x*,struct emu10k1x_midi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1x_midi_input_open(struct snd_rawmidi_substream *substream)
{
	struct emu10k1x *emu;
	struct emu10k1x_midi *midi = substream->rmidi->private_data;
	unsigned long flags;
	
	emu = midi->emu;
	if (snd_BUG_ON(!emu))
		return -ENXIO;
	spin_lock_irqsave(&midi->open_lock, flags);
	midi->midi_mode |= EMU10K1X_MIDI_MODE_INPUT;
	midi->substream_input = substream;
	if (!(midi->midi_mode & EMU10K1X_MIDI_MODE_OUTPUT)) {
		spin_unlock_irqrestore(&midi->open_lock, flags);
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_RESET, 1))
			goto error_out;
		if (snd_emu10k1x_midi_cmd(emu, midi, MPU401_ENTER_UART, 1))
			goto error_out;
	} else {
		spin_unlock_irqrestore(&midi->open_lock, flags);
	}
	return 0;

error_out:
	return -EIO;
}