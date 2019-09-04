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
struct me_private_data {scalar_t__ ctrl2; scalar_t__ ctrl1; scalar_t__ dac_ctrl; } ;
struct comedi_device {scalar_t__ mmio; struct me_private_data* private; } ;

/* Variables and functions */
 scalar_t__ ME_CTRL1_REG ; 
 scalar_t__ ME_CTRL2_REG ; 
 scalar_t__ ME_DAC_CTRL_REG ; 
 scalar_t__ ME_STATUS_REG ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int me_reset(struct comedi_device *dev)
{
	struct me_private_data *devpriv = dev->private;

	/* Reset board */
	writew(0x00, dev->mmio + ME_CTRL1_REG);
	writew(0x00, dev->mmio + ME_CTRL2_REG);
	writew(0x00, dev->mmio + ME_STATUS_REG);	/* clear interrupts */
	writew(0x00, dev->mmio + ME_DAC_CTRL_REG);

	/* Save values in the board context */
	devpriv->dac_ctrl = 0;
	devpriv->ctrl1 = 0;
	devpriv->ctrl2 = 0;

	return 0;
}