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
typedef  int /*<<< orphan*/  u32 ;
struct i2sbus_dev {int /*<<< orphan*/  low_lock; TYPE_1__* intfregs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  intr_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  in_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i2sbus_bus_intr(int irq, void *devid)
{
	struct i2sbus_dev *dev = devid;
	u32 intreg;

	spin_lock(&dev->low_lock);
	intreg = in_le32(&dev->intfregs->intr_ctl);

	/* acknowledge interrupt reasons */
	out_le32(&dev->intfregs->intr_ctl, intreg);

	spin_unlock(&dev->low_lock);

	return IRQ_HANDLED;
}