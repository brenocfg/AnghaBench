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
struct snd_cs46xx {int midcr; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct snd_cs46xx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_MIDCR ; 
 int /*<<< orphan*/  BA0_MIDSR ; 
 int /*<<< orphan*/  BA0_MIDWP ; 
 int MIDCR_TIE ; 
 int MIDSR_TBF ; 
 int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned char) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs46xx_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct snd_cs46xx *chip = substream->rmidi->private_data;
	unsigned char byte;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (up) {
		if ((chip->midcr & MIDCR_TIE) == 0) {
			chip->midcr |= MIDCR_TIE;
			/* fill UART FIFO buffer at first, and turn Tx interrupts only if necessary */
			while ((chip->midcr & MIDCR_TIE) &&
			       (snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_TBF) == 0) {
				if (snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					chip->midcr &= ~MIDCR_TIE;
				} else {
					snd_cs46xx_pokeBA0(chip, BA0_MIDWP, byte);
				}
			}
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	} else {
		if (chip->midcr & MIDCR_TIE) {
			chip->midcr &= ~MIDCR_TIE;
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}