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
typedef  int u32 ;
struct intel8x0 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_INTERRUPTSR ; 
 int ALI_INT_GPIO ; 
 int /*<<< orphan*/  ALI_RTSR ; 
 int /*<<< orphan*/  ALI_SCR ; 
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_ali_reset (struct intel8x0*) ; 
 int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static int snd_intel8x0_ali_chip_init(struct intel8x0 *chip, int probing)
{
	u32 reg;
	int i = 0;

	reg = igetdword(chip, ICHREG(ALI_SCR));
	if ((reg & 2) == 0)	/* Cold required */
		reg |= 2;
	else
		reg |= 1;	/* Warm */
	reg &= ~0x80000000;	/* ACLink on */
	iputdword(chip, ICHREG(ALI_SCR), reg);

	for (i = 0; i < HZ / 2; i++) {
		if (! (igetdword(chip, ICHREG(ALI_INTERRUPTSR)) & ALI_INT_GPIO))
			goto __ok;
		schedule_timeout_uninterruptible(1);
	}
	dev_err(chip->card->dev, "AC'97 reset failed.\n");
	if (probing)
		return -EIO;

 __ok:
	for (i = 0; i < HZ / 2; i++) {
		reg = igetdword(chip, ICHREG(ALI_RTSR));
		if (reg & 0x80) /* primary codec */
			break;
		iputdword(chip, ICHREG(ALI_RTSR), reg | 0x80);
		schedule_timeout_uninterruptible(1);
	}

	do_ali_reset(chip);
	return 0;
}