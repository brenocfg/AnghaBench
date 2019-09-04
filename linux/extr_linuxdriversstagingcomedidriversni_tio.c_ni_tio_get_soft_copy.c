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
struct ni_gpct_device {unsigned int* regs; int /*<<< orphan*/  regs_lock; } ;
struct ni_gpct {struct ni_gpct_device* counter_dev; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;

/* Variables and functions */
 int NITIO_NUM_REGS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned int ni_tio_get_soft_copy(const struct ni_gpct *counter,
				  enum ni_gpct_register reg)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int value = 0;
	unsigned long flags;

	if (reg < NITIO_NUM_REGS) {
		spin_lock_irqsave(&counter_dev->regs_lock, flags);
		value = counter_dev->regs[reg];
		spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
	}
	return value;
}