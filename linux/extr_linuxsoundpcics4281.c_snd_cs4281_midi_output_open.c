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
struct cs4281 {int uartm; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  midcr; struct snd_rawmidi_substream* midi_output; } ;
struct TYPE_2__ {struct cs4281* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_MIDCR ; 
 int /*<<< orphan*/  BA0_MIDCR_TXE ; 
 int CS4281_MODE_INPUT ; 
 int CS4281_MODE_OUTPUT ; 
 int /*<<< orphan*/  snd_cs4281_midi_reset (struct cs4281*) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cs4281_midi_output_open(struct snd_rawmidi_substream *substream)
{
	struct cs4281 *chip = substream->rmidi->private_data;

	spin_lock_irq(&chip->reg_lock);
	chip->uartm |= CS4281_MODE_OUTPUT;
	chip->midcr |= BA0_MIDCR_TXE;
	chip->midi_output = substream;
	if (!(chip->uartm & CS4281_MODE_INPUT)) {
		snd_cs4281_midi_reset(chip);
	} else {
		snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	}
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}