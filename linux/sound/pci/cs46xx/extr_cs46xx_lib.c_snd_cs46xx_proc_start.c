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
 int /*<<< orphan*/  BA1_FRMT ; 
 int /*<<< orphan*/  BA1_SPCR ; 
 int SPCR_DRQEN ; 
 int SPCR_RUN ; 
 int SPCR_RUNFR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_cs46xx_peek (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cs46xx_proc_start(struct snd_cs46xx *chip)
{
	int cnt;

	/*
	 *  Set the frame timer to reflect the number of cycles per frame.
	 */
	snd_cs46xx_poke(chip, BA1_FRMT, 0xadf);
	/*
	 *  Turn on the run, run at frame, and DMA enable bits in the local copy of
	 *  the SP control register.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_RUN | SPCR_RUNFR | SPCR_DRQEN);
	/*
	 *  Wait until the run at frame bit resets itself in the SP control
	 *  register.
	 */
	for (cnt = 0; cnt < 25; cnt++) {
		udelay(50);
		if (!(snd_cs46xx_peek(chip, BA1_SPCR) & SPCR_RUNFR))
			break;
	}

	if (snd_cs46xx_peek(chip, BA1_SPCR) & SPCR_RUNFR)
		dev_err(chip->card->dev, "SPCR_RUNFR never reset\n");
}