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
struct fm801 {scalar_t__ irq; } ;

/* Variables and functions */
 unsigned short FM801_IRQ_CAPTURE ; 
 unsigned short FM801_IRQ_MPU ; 
 unsigned short FM801_IRQ_PLAYBACK ; 
 int /*<<< orphan*/  FM_VOL ; 
 int /*<<< orphan*/  I2S_MODE ; 
 int /*<<< orphan*/  I2S_VOL ; 
 int /*<<< orphan*/  IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  PCM_VOL ; 
 unsigned short fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm801_writew (struct fm801*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void snd_fm801_chip_init(struct fm801 *chip)
{
	unsigned short cmdw;

	/* init volume */
	fm801_writew(chip, PCM_VOL, 0x0808);
	fm801_writew(chip, FM_VOL, 0x9f1f);
	fm801_writew(chip, I2S_VOL, 0x8808);

	/* I2S control - I2S mode */
	fm801_writew(chip, I2S_MODE, 0x0003);

	/* interrupt setup */
	cmdw = fm801_readw(chip, IRQ_MASK);
	if (chip->irq < 0)
		cmdw |= 0x00c3;		/* mask everything, no PCM nor MPU */
	else
		cmdw &= ~0x0083;	/* unmask MPU, PLAYBACK & CAPTURE */
	fm801_writew(chip, IRQ_MASK, cmdw);

	/* interrupt clear */
	fm801_writew(chip, IRQ_STATUS,
		     FM801_IRQ_PLAYBACK | FM801_IRQ_CAPTURE | FM801_IRQ_MPU);
}