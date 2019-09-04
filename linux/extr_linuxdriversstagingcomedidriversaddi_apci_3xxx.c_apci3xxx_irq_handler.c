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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ mmio; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t apci3xxx_irq_handler(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int status;
	unsigned int val;

	/* Test if interrupt occur */
	status = readl(dev->mmio + 16);
	if ((status & 0x2) == 0x2) {
		/* Reset the interrupt */
		writel(status, dev->mmio + 16);

		val = readl(dev->mmio + 28);
		comedi_buf_write_samples(s, &val, 1);

		s->async->events |= COMEDI_CB_EOA;
		comedi_handle_events(dev, s);

		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}