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
struct comedi_subdevice {int state; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; struct apci1032_private* private; } ;
struct apci1032_private {scalar_t__ amcc_iobase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 unsigned int APCI1032_CTRL_INT_ENA ; 
 scalar_t__ APCI1032_CTRL_REG ; 
 scalar_t__ APCI1032_STATUS_REG ; 
 int INTCSR_INTR_ASSERTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t apci1032_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct apci1032_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned int ctrl;

	/* check interrupt is from this device */
	if ((inl(devpriv->amcc_iobase + AMCC_OP_REG_INTCSR) &
	     INTCSR_INTR_ASSERTED) == 0)
		return IRQ_NONE;

	/* check interrupt is enabled */
	ctrl = inl(dev->iobase + APCI1032_CTRL_REG);
	if ((ctrl & APCI1032_CTRL_INT_ENA) == 0)
		return IRQ_HANDLED;

	/* disable the interrupt */
	outl(ctrl & ~APCI1032_CTRL_INT_ENA, dev->iobase + APCI1032_CTRL_REG);

	s->state = inl(dev->iobase + APCI1032_STATUS_REG) & 0xffff;
	comedi_buf_write_samples(s, &s->state, 1);
	comedi_handle_events(dev, s);

	/* enable the interrupt */
	outl(ctrl, dev->iobase + APCI1032_CTRL_REG);

	return IRQ_HANDLED;
}