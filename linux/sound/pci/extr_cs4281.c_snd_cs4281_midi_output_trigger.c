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
struct cs4281 {int midcr; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct cs4281* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_MIDCR ; 
 int BA0_MIDCR_TIE ; 
 int /*<<< orphan*/  BA0_MIDSR ; 
 int BA0_MIDSR_TBF ; 
 int /*<<< orphan*/  BA0_MIDWP ; 
 int snd_cs4281_peekBA0 (struct cs4281*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,unsigned char) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4281_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct cs4281 *chip = substream->rmidi->private_data;
	unsigned char byte;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (up) {
		if ((chip->midcr & BA0_MIDCR_TIE) == 0) {
			chip->midcr |= BA0_MIDCR_TIE;
			/* fill UART FIFO buffer at first, and turn Tx interrupts only if necessary */
			while ((chip->midcr & BA0_MIDCR_TIE) &&
			       (snd_cs4281_peekBA0(chip, BA0_MIDSR) & BA0_MIDSR_TBF) == 0) {
				if (snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					chip->midcr &= ~BA0_MIDCR_TIE;
				} else {
					snd_cs4281_pokeBA0(chip, BA0_MIDWP, byte);
				}
			}
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	} else {
		if (chip->midcr & BA0_MIDCR_TIE) {
			chip->midcr &= ~BA0_MIDCR_TIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}