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
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* read_subdev; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ stop_src; scalar_t__ stop_arg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  DMM32AT_CTRL_INTRST ; 
 scalar_t__ DMM32AT_CTRL_REG ; 
 unsigned char DMM32AT_INTCLK_ADINT ; 
 scalar_t__ DMM32AT_INTCLK_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int dmm32at_ai_get_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t dmm32at_isr(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned char intstat;
	unsigned int val;
	int i;

	if (!dev->attached) {
		dev_err(dev->class_dev, "spurious interrupt\n");
		return IRQ_HANDLED;
	}

	intstat = inb(dev->iobase + DMM32AT_INTCLK_REG);

	if (intstat & DMM32AT_INTCLK_ADINT) {
		struct comedi_subdevice *s = dev->read_subdev;
		struct comedi_cmd *cmd = &s->async->cmd;

		for (i = 0; i < cmd->chanlist_len; i++) {
			val = dmm32at_ai_get_sample(dev, s);
			comedi_buf_write_samples(s, &val, 1);
		}

		if (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_done >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;

		comedi_handle_events(dev, s);
	}

	/* reset the interrupt */
	outb(DMM32AT_CTRL_INTRST, dev->iobase + DMM32AT_CTRL_REG);
	return IRQ_HANDLED;
}