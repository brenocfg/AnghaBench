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
struct comedi_device {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_CONTROL ; 
 int /*<<< orphan*/  das800_ind_write (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void das800_disable(struct comedi_device *dev)
{
	unsigned long irq_flags;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	/* disable hardware triggering of conversions */
	das800_ind_write(dev, 0x0, CONV_CONTROL);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
}