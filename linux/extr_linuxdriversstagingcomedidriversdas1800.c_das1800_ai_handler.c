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
struct das1800_private {int irq_dma_bits; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct comedi_subdevice* read_subdev; struct das1800_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int ADC ; 
 unsigned int CLEAR_INTR_MASK ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 unsigned int CT0TC ; 
 scalar_t__ DAS1800_SELECT ; 
 scalar_t__ DAS1800_STATUS ; 
 int DMA_ENABLED ; 
 unsigned int FHF ; 
 unsigned int FNE ; 
 unsigned int OVF ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_flush_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_handle_dma (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  das1800_handle_fifo_half_full (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_handle_fifo_not_empty (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das1800_ai_handler(struct comedi_device *dev)
{
	struct das1800_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int status = inb(dev->iobase + DAS1800_STATUS);

	/* select adc register (spinlock is already held) */
	outb(ADC, dev->iobase + DAS1800_SELECT);

	/* get samples with dma, fifo, or polled as necessary */
	if (devpriv->irq_dma_bits & DMA_ENABLED)
		das1800_handle_dma(dev, s, status);
	else if (status & FHF)
		das1800_handle_fifo_half_full(dev, s);
	else if (status & FNE)
		das1800_handle_fifo_not_empty(dev, s);

	/* if the card's fifo has overflowed */
	if (status & OVF) {
		/*  clear OVF interrupt bit */
		outb(CLEAR_INTR_MASK & ~OVF, dev->iobase + DAS1800_STATUS);
		dev_err(dev->class_dev, "FIFO overflow\n");
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		return;
	}
	/*  stop taking data if appropriate */
	/* stop_src TRIG_EXT */
	if (status & CT0TC) {
		/*  clear CT0TC interrupt bit */
		outb(CLEAR_INTR_MASK & ~CT0TC, dev->iobase + DAS1800_STATUS);
		/* get all remaining samples before quitting */
		if (devpriv->irq_dma_bits & DMA_ENABLED)
			das1800_flush_dma(dev, s);
		else
			das1800_handle_fifo_not_empty(dev, s);
		async->events |= COMEDI_CB_EOA;
	} else if (cmd->stop_src == TRIG_COUNT &&
		   async->scans_done >= cmd->stop_arg) {
		async->events |= COMEDI_CB_EOA;
	}

	comedi_handle_events(dev, s);
}