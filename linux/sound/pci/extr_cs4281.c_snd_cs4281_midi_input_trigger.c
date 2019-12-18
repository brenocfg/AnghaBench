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
 int BA0_MIDCR_RIE ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4281_midi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct cs4281 *chip = substream->rmidi->private_data;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (up) {
		if ((chip->midcr & BA0_MIDCR_RIE) == 0) {
			chip->midcr |= BA0_MIDCR_RIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	} else {
		if (chip->midcr & BA0_MIDCR_RIE) {
			chip->midcr &= ~BA0_MIDCR_RIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		}
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}