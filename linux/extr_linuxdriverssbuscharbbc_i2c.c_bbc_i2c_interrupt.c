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
struct bbc_i2c_bus {int /*<<< orphan*/  wq; scalar_t__ i2c_control_regs; scalar_t__ waiting; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int I2C_PCF_PIN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bbc_i2c_interrupt(int irq, void *dev_id)
{
	struct bbc_i2c_bus *bp = dev_id;

	/* PIN going from set to clear is the only event which
	 * makes the i2c assert an interrupt.
	 */
	if (bp->waiting &&
	    !(readb(bp->i2c_control_regs + 0x0) & I2C_PCF_PIN))
		wake_up_interruptible(&bp->wq);

	return IRQ_HANDLED;
}