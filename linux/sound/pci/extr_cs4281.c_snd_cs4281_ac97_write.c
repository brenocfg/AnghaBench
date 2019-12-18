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
struct snd_ac97 {scalar_t__ num; struct cs4281* private_data; } ;
struct cs4281 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_ACCAD ; 
 int /*<<< orphan*/  BA0_ACCDA ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 unsigned short BA0_ACCTL_DCV ; 
 unsigned short BA0_ACCTL_ESYN ; 
 unsigned short BA0_ACCTL_TC ; 
 unsigned short BA0_ACCTL_VFRM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short,unsigned short) ; 
 unsigned short snd_cs4281_peekBA0 (struct cs4281*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cs4281_ac97_write(struct snd_ac97 *ac97,
				  unsigned short reg, unsigned short val)
{
	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch for AC97 register address
	 *  2. Write ACCDA = Command Data Register = 470h    for data to write to AC97
	 *  3. Write ACCTL = Control Register = 460h for initiating the write
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 07h
	 *  5. if DCV not cleared, break and return error
	 */
	struct cs4281 *chip = ac97->private_data;
	int count;

	/*
	 *  Setup the AC97 control registers on the CS461x to send the
	 *  appropriate command to the AC97 to perform the read.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  reset CRW - Write command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
         */
	snd_cs4281_pokeBA0(chip, BA0_ACCAD, reg);
	snd_cs4281_pokeBA0(chip, BA0_ACCDA, val);
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_DCV | BA0_ACCTL_VFRM |
				            BA0_ACCTL_ESYN | (ac97->num ? BA0_ACCTL_TC : 0));
	for (count = 0; count < 2000; count++) {
		/*
		 *  First, we want to wait for a short time.
		 */
		udelay(10);
		/*
		 *  Now, check to see if the write has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 07h
		 */
		if (!(snd_cs4281_peekBA0(chip, BA0_ACCTL) & BA0_ACCTL_DCV)) {
			return;
		}
	}
	dev_err(chip->card->dev,
		"AC'97 write problem, reg = 0x%x, val = 0x%x\n", reg, val);
}