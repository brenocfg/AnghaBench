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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_isadma_desc {unsigned short* virt_addr; unsigned int size; int /*<<< orphan*/  chan; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct a2150_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct a2150_private {unsigned int count; struct comedi_isadma* dma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int DMA_TC_BIT ; 
 scalar_t__ DMA_TC_CLEAR_REG ; 
 int INTR_BIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OVFL_BIT ; 
 scalar_t__ STATUS_REG ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NONE ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_isadma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 unsigned int comedi_samples_to_bytes (struct comedi_subdevice*,unsigned int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t a2150_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct a2150_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc = &dma->desc[0];
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned short *buf = desc->virt_addr;
	unsigned int max_points, num_points, residue, leftover;
	unsigned short dpnt;
	int status;
	int i;

	if (!dev->attached)
		return IRQ_HANDLED;

	status = inw(dev->iobase + STATUS_REG);
	if ((status & INTR_BIT) == 0)
		return IRQ_NONE;

	if (status & OVFL_BIT) {
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
	}

	if ((status & DMA_TC_BIT) == 0) {
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		return IRQ_HANDLED;
	}

	/*
	 * residue is the number of bytes left to be done on the dma
	 * transfer.  It should always be zero at this point unless
	 * the stop_src is set to external triggering.
	 */
	residue = comedi_isadma_disable(desc->chan);

	/* figure out how many points to read */
	max_points = comedi_bytes_to_samples(s, desc->size);
	num_points = max_points - comedi_bytes_to_samples(s, residue);
	if (devpriv->count < num_points && cmd->stop_src == TRIG_COUNT)
		num_points = devpriv->count;

	/* figure out how many points will be stored next time */
	leftover = 0;
	if (cmd->stop_src == TRIG_NONE) {
		leftover = comedi_bytes_to_samples(s, desc->size);
	} else if (devpriv->count > max_points) {
		leftover = devpriv->count - max_points;
		if (leftover > max_points)
			leftover = max_points;
	}
	/*
	 * There should only be a residue if collection was stopped by having
	 * the stop_src set to an external trigger, in which case there
	 * will be no more data
	 */
	if (residue)
		leftover = 0;

	for (i = 0; i < num_points; i++) {
		/* write data point to comedi buffer */
		dpnt = buf[i];
		/* convert from 2's complement to unsigned coding */
		dpnt ^= 0x8000;
		comedi_buf_write_samples(s, &dpnt, 1);
		if (cmd->stop_src == TRIG_COUNT) {
			if (--devpriv->count == 0) {	/* end of acquisition */
				async->events |= COMEDI_CB_EOA;
				break;
			}
		}
	}
	/* re-enable dma */
	if (leftover) {
		desc->size = comedi_samples_to_bytes(s, leftover);
		comedi_isadma_program(desc);
	}

	comedi_handle_events(dev, s);

	/* clear interrupt */
	outw(0x00, dev->iobase + DMA_TC_CLEAR_REG);

	return IRQ_HANDLED;
}