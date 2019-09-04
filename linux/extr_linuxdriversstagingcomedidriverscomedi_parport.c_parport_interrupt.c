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
struct comedi_subdevice {int /*<<< orphan*/  state; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int PARPORT_CTRL_IRQ_ENA ; 
 scalar_t__ PARPORT_CTRL_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static irqreturn_t parport_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int ctrl;

	ctrl = inb(dev->iobase + PARPORT_CTRL_REG);
	if (!(ctrl & PARPORT_CTRL_IRQ_ENA))
		return IRQ_NONE;

	comedi_buf_write_samples(s, &s->state, 1);
	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}