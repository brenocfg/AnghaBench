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
struct intel8x0 {unsigned int int_sta_mask; unsigned int bdbars_count; int /*<<< orphan*/  int_sta_reg; struct ichdev* ichd; int /*<<< orphan*/  buggy_irq; } ;
struct ichdev {unsigned int int_sta_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_intel8x0_update (struct intel8x0*,struct ichdev*) ; 

__attribute__((used)) static irqreturn_t snd_intel8x0_interrupt(int irq, void *dev_id)
{
	struct intel8x0 *chip = dev_id;
	struct ichdev *ichdev;
	unsigned int status;
	unsigned int i;

	status = igetdword(chip, chip->int_sta_reg);
	if (status == 0xffffffff)	/* we are not yet resumed */
		return IRQ_NONE;

	if ((status & chip->int_sta_mask) == 0) {
		if (status) {
			/* ack */
			iputdword(chip, chip->int_sta_reg, status);
			if (! chip->buggy_irq)
				status = 0;
		}
		return IRQ_RETVAL(status);
	}

	for (i = 0; i < chip->bdbars_count; i++) {
		ichdev = &chip->ichd[i];
		if (status & ichdev->int_sta_mask)
			snd_intel8x0_update(chip, ichdev);
	}

	/* ack them */
	iputdword(chip, chip->int_sta_reg, status & chip->int_sta_mask);
	
	return IRQ_HANDLED;
}