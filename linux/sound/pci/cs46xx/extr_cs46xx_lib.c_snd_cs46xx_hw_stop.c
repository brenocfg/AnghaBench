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
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA1_CCTL ; 
 int /*<<< orphan*/  BA1_CIE ; 
 int /*<<< orphan*/  BA1_PCTL ; 
 int /*<<< orphan*/  BA1_PFIE ; 
 unsigned int CLKCR1_SWCE ; 
 unsigned int snd_cs46xx_peek (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 unsigned int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cs46xx_proc_stop (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  snd_cs46xx_reset (struct snd_cs46xx*) ; 

__attribute__((used)) static void snd_cs46xx_hw_stop(struct snd_cs46xx *chip)
{
	unsigned int tmp;

	tmp = snd_cs46xx_peek(chip, BA1_PFIE);
	tmp &= ~0x0000f03f;
	tmp |=  0x00000010;
	snd_cs46xx_poke(chip, BA1_PFIE, tmp);	/* playback interrupt disable */

	tmp = snd_cs46xx_peek(chip, BA1_CIE);
	tmp &= ~0x0000003f;
	tmp |=  0x00000011;
	snd_cs46xx_poke(chip, BA1_CIE, tmp);	/* capture interrupt disable */

	/*
         *  Stop playback DMA.
	 */
	tmp = snd_cs46xx_peek(chip, BA1_PCTL);
	snd_cs46xx_poke(chip, BA1_PCTL, tmp & 0x0000ffff);

	/*
         *  Stop capture DMA.
	 */
	tmp = snd_cs46xx_peek(chip, BA1_CCTL);
	snd_cs46xx_poke(chip, BA1_CCTL, tmp & 0xffff0000);

	/*
         *  Reset the processor.
         */
	snd_cs46xx_reset(chip);

	snd_cs46xx_proc_stop(chip);

	/*
	 *  Power down the PLL.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, 0);

	/*
	 *  Turn off the Processor by turning off the software clock enable flag in 
	 *  the clock control register.
	 */
	tmp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1) & ~CLKCR1_SWCE;
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, tmp);
}