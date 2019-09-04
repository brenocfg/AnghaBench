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
struct snd_cs46xx {int amplifier; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_EGPIODR ; 
 int /*<<< orphan*/  BA0_EGPIOPTR ; 
 int EGPIODR_GPOE2 ; 
 int EGPIOPTR_GPPT2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amp_hercules(struct snd_cs46xx *chip, int change)
{
	int old = chip->amplifier;
	int val1 = snd_cs46xx_peekBA0(chip, BA0_EGPIODR);
	int val2 = snd_cs46xx_peekBA0(chip, BA0_EGPIOPTR);

	chip->amplifier += change;
	if (chip->amplifier && !old) {
		dev_dbg(chip->card->dev, "Hercules amplifier ON\n");

		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, 
				   EGPIODR_GPOE2 | val1);     /* enable EGPIO2 output */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, 
				   EGPIOPTR_GPPT2 | val2);   /* open-drain on output */
	} else if (old && !chip->amplifier) {
		dev_dbg(chip->card->dev, "Hercules amplifier OFF\n");
		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR,  val1 & ~EGPIODR_GPOE2); /* disable */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, val2 & ~EGPIOPTR_GPPT2); /* disable */
	}
}