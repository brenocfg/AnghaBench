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
struct snd_cs46xx {int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short ACCTL_DCV ; 
 unsigned short ACCTL_ESYN ; 
 unsigned short ACCTL_RSTN ; 
 unsigned short ACCTL_TC ; 
 unsigned short ACCTL_VFRM ; 
 int /*<<< orphan*/  BA0_ACCAD ; 
 int /*<<< orphan*/  BA0_ACCDA ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 int CS46XX_PRIMARY_CODEC_INDEX ; 
 int CS46XX_SECONDARY_CODEC_INDEX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned short,unsigned short) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 unsigned short snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cs46xx_codec_write(struct snd_cs46xx *chip,
				   unsigned short reg,
				   unsigned short val,
				   int codec_index)
{
	int count;

	if (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		return;

	chip->active_ctrl(chip, 1);

	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch for AC97 register address
	 *  2. Write ACCDA = Command Data Register = 470h    for data to write to AC97
	 *  3. Write ACCTL = Control Register = 460h for initiating the write
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 07h
	 *  5. if DCV not cleared, break and return error
	 */

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
	snd_cs46xx_pokeBA0(chip, BA0_ACCAD , reg);
	snd_cs46xx_pokeBA0(chip, BA0_ACCDA , val);
	snd_cs46xx_peekBA0(chip, BA0_ACCTL);

	if (codec_index == CS46XX_PRIMARY_CODEC_INDEX) {
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, /* clear ACCTL_DCV */ ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
	} else {
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_TC |
				   ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
	}

	for (count = 0; count < 4000; count++) {
		/*
		 *  First, we want to wait for a short time.
		 */
		udelay(10);
		/*
		 *  Now, check to see if the write has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 07h
		 */
		if (!(snd_cs46xx_peekBA0(chip, BA0_ACCTL) & ACCTL_DCV)) {
			goto end;
		}
	}
	dev_err(chip->card->dev,
		"AC'97 write problem, codec_index = %d, reg = 0x%x, val = 0x%x\n",
		codec_index, reg, val);
 end:
	chip->active_ctrl(chip, -1);
}