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
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  ni_tio_write (struct ni_gpct*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ni_tio_set_bits_transient(struct ni_gpct *counter,
				      enum ni_gpct_register reg,
				      unsigned int mask, unsigned int value,
				      unsigned int transient)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned long flags;

	if (reg < NITIO_NUM_REGS) {
		spin_lock_irqsave(&counter_dev->regs_lock, flags);
		counter_dev->regs[reg] &= ~mask;
		counter_dev->regs[reg] |= (value & mask);
		ni_tio_write(counter, counter_dev->regs[reg] | transient, reg);
		mmiowb();
		spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
	}
}