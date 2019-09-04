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
typedef  int u32 ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ mmio; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  S626_IRQ_GPIO3 129 
#define  S626_IRQ_RPS1 128 
 scalar_t__ S626_P_IER ; 
 scalar_t__ S626_P_ISR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s626_check_counter_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  s626_check_dio_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  s626_handle_eos_interrupt (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t s626_irq_handler(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned long flags;
	u32 irqtype, irqstatus;

	if (!dev->attached)
		return IRQ_NONE;
	/* lock to avoid race with comedi_poll */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* save interrupt enable register state */
	irqstatus = readl(dev->mmio + S626_P_IER);

	/* read interrupt type */
	irqtype = readl(dev->mmio + S626_P_ISR);

	/* disable master interrupt */
	writel(0, dev->mmio + S626_P_IER);

	/* clear interrupt */
	writel(irqtype, dev->mmio + S626_P_ISR);

	switch (irqtype) {
	case S626_IRQ_RPS1:	/* end_of_scan occurs */
		if (s626_handle_eos_interrupt(dev))
			irqstatus = 0;
		break;
	case S626_IRQ_GPIO3:	/* check dio and counter interrupt */
		/* s626_dio_clear_irq(dev); */
		s626_check_dio_interrupts(dev);
		s626_check_counter_interrupts(dev);
		break;
	}

	/* enable interrupt */
	writel(irqstatus, dev->mmio + S626_P_IER);

	spin_unlock_irqrestore(&dev->spinlock, flags);
	return IRQ_HANDLED;
}