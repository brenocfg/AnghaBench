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
struct snd_ac97 {int num; struct cs4281* private_data; } ;
struct cs4281 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_ACCAD ; 
 int /*<<< orphan*/  BA0_ACCDA ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 int BA0_ACCTL_CRW ; 
 int BA0_ACCTL_DCV ; 
 int BA0_ACCTL_ESYN ; 
 int BA0_ACCTL_TC ; 
 int BA0_ACCTL_VFRM ; 
 int /*<<< orphan*/  BA0_ACSDA ; 
 int /*<<< orphan*/  BA0_ACSDA2 ; 
 int /*<<< orphan*/  BA0_ACSTS ; 
 int /*<<< orphan*/  BA0_ACSTS2 ; 
 int BA0_ACSTS_VSTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int snd_cs4281_peekBA0 (struct cs4281*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short snd_cs4281_ac97_read(struct snd_ac97 *ac97,
					   unsigned short reg)
{
	struct cs4281 *chip = ac97->private_data;
	int count;
	unsigned short result;
	// FIXME: volatile is necessary in the following due to a bug of
	// some gcc versions
	volatile int ac97_num = ((volatile struct snd_ac97 *)ac97)->num;

	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch for AC97 register address
	 *  2. Write ACCDA = Command Data Register = 470h    for data to write to AC97 
	 *  3. Write ACCTL = Control Register = 460h for initiating the write
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 17h
	 *  5. if DCV not cleared, break and return error
	 *  6. Read ACSTS = Status Register = 464h, check VSTS bit
	 */

	snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSDA2 : BA0_ACSDA);

	/*
	 *  Setup the AC97 control registers on the CS461x to send the
	 *  appropriate command to the AC97 to perform the read.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  set CRW - Read command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
	 */

	snd_cs4281_pokeBA0(chip, BA0_ACCAD, reg);
	snd_cs4281_pokeBA0(chip, BA0_ACCDA, 0);
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_DCV | BA0_ACCTL_CRW |
					    BA0_ACCTL_VFRM | BA0_ACCTL_ESYN |
			   (ac97_num ? BA0_ACCTL_TC : 0));


	/*
	 *  Wait for the read to occur.
	 */
	for (count = 0; count < 500; count++) {
		/*
		 *  First, we want to wait for a short time.
	 	 */
		udelay(10);
		/*
		 *  Now, check to see if the read has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 17h
		 */
		if (!(snd_cs4281_peekBA0(chip, BA0_ACCTL) & BA0_ACCTL_DCV))
			goto __ok1;
	}

	dev_err(chip->card->dev,
		"AC'97 read problem (ACCTL_DCV), reg = 0x%x\n", reg);
	result = 0xffff;
	goto __end;
	
      __ok1:
	/*
	 *  Wait for the valid status bit to go active.
	 */
	for (count = 0; count < 100; count++) {
		/*
		 *  Read the AC97 status register.
		 *  ACSTS = Status Register = 464h
		 *  VSTS - Valid Status
		 */
		if (snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSTS2 : BA0_ACSTS) & BA0_ACSTS_VSTS)
			goto __ok2;
		udelay(10);
	}
	
	dev_err(chip->card->dev,
		"AC'97 read problem (ACSTS_VSTS), reg = 0x%x\n", reg);
	result = 0xffff;
	goto __end;

      __ok2:
	/*
	 *  Read the data returned from the AC97 register.
	 *  ACSDA = Status Data Register = 474h
	 */
	result = snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSDA2 : BA0_ACSDA);

      __end:
	return result;
}