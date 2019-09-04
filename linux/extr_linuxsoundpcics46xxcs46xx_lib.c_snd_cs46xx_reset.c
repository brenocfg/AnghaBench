#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_cs46xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_DREG ; 
 int /*<<< orphan*/  BA1_FRMT ; 
 int /*<<< orphan*/  BA1_SPCR ; 
 int /*<<< orphan*/  BA1_TWPR ; 
 int DREG_REGID_TRAP_SELECT ; 
 int SPCR_DRQEN ; 
 int SPCR_RSTSP ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_cs46xx_reset(struct snd_cs46xx *chip)
{
	int idx;

	/*
	 *  Write the reset bit of the SP control register.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_RSTSP);

	/*
	 *  Write the control register.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_DRQEN);

	/*
	 *  Clear the trap registers.
	 */
	for (idx = 0; idx < 8; idx++) {
		snd_cs46xx_poke(chip, BA1_DREG, DREG_REGID_TRAP_SELECT + idx);
		snd_cs46xx_poke(chip, BA1_TWPR, 0xFFFF);
	}
	snd_cs46xx_poke(chip, BA1_DREG, 0);

	/*
	 *  Set the frame timer to reflect the number of cycles per frame.
	 */
	snd_cs46xx_poke(chip, BA1_FRMT, 0xadf);
}