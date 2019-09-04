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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AD_FIFO_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static irqreturn_t atmio16d_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	unsigned short val;

	val = inw(dev->iobase + AD_FIFO_REG);
	comedi_buf_write_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}