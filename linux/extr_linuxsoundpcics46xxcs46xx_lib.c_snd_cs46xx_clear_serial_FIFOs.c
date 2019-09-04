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
struct snd_cs46xx {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA0_SERBAD ; 
 int /*<<< orphan*/  BA0_SERBCM ; 
 int /*<<< orphan*/  BA0_SERBWP ; 
 unsigned int CLKCR1_SWCE ; 
 unsigned int SERBCM_WRC ; 
 scalar_t__ cs46xx_wait_for_fifo (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void snd_cs46xx_clear_serial_FIFOs(struct snd_cs46xx *chip)
{
	int idx, powerdown = 0;
	unsigned int tmp;

	/*
	 *  See if the devices are powered down.  If so, we must power them up first
	 *  or they will not respond.
	 */
	tmp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1);
	if (!(tmp & CLKCR1_SWCE)) {
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, tmp | CLKCR1_SWCE);
		powerdown = 1;
	}

	/*
	 *  We want to clear out the serial port FIFOs so we don't end up playing
	 *  whatever random garbage happens to be in them.  We fill the sample FIFOS
	 *  with zero (silence).
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERBWP, 0);

	/*
	 *  Fill all 256 sample FIFO locations.
	 */
	for (idx = 0; idx < 0xFF; idx++) {
		/*
		 *  Make sure the previous FIFO write operation has completed.
		 */
		if (cs46xx_wait_for_fifo(chip,1)) {
			dev_dbg(chip->card->dev,
				"failed waiting for FIFO at addr (%02X)\n",
				idx);

			if (powerdown)
				snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, tmp);
          
			break;
		}
		/*
		 *  Write the serial port FIFO index.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBAD, idx);
		/*
		 *  Tell the serial port to load the new value into the FIFO location.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBCM, SERBCM_WRC);
	}
	/*
	 *  Now, if we powered up the devices, then power them back down again.
	 *  This is kinda ugly, but should never happen.
	 */
	if (powerdown)
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, tmp);
}