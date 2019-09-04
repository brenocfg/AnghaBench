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
struct labpc_private {int stat1; int (* read_byte ) (struct comedi_device*,int /*<<< orphan*/ ) ;int stat2; scalar_t__ current_transfer; scalar_t__ count; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct labpc_boardinfo {scalar_t__ is_labpc1200; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct labpc_private* private; struct labpc_boardinfo* board_ptr; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_CLEAR_REG ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int STAT1_CNTINT ; 
 int STAT1_DAVAIL ; 
 int STAT1_GATA0 ; 
 int STAT1_OVERFLOW ; 
 int STAT1_OVERRUN ; 
 int /*<<< orphan*/  STAT1_REG ; 
 int STAT2_FIFONHF ; 
 int STAT2_OUTA1 ; 
 int /*<<< orphan*/  STAT2_REG ; 
 int /*<<< orphan*/  TIMER_CLEAR_REG ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_dma_transfer ; 
 int /*<<< orphan*/  labpc_drain_dregs (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_drain_fifo (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_handle_dma_status (struct comedi_device*) ; 
 int stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t labpc_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	const struct labpc_boardinfo *board = dev->board_ptr;
	struct labpc_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async;
	struct comedi_cmd *cmd;

	if (!dev->attached) {
		dev_err(dev->class_dev, "premature interrupt\n");
		return IRQ_HANDLED;
	}

	async = s->async;
	cmd = &async->cmd;

	/* read board status */
	devpriv->stat1 = devpriv->read_byte(dev, STAT1_REG);
	if (board->is_labpc1200)
		devpriv->stat2 = devpriv->read_byte(dev, STAT2_REG);

	if ((devpriv->stat1 & (STAT1_GATA0 | STAT1_CNTINT | STAT1_OVERFLOW |
			       STAT1_OVERRUN | STAT1_DAVAIL)) == 0 &&
	    (devpriv->stat2 & STAT2_OUTA1) == 0 &&
	    (devpriv->stat2 & STAT2_FIFONHF)) {
		return IRQ_NONE;
	}

	if (devpriv->stat1 & STAT1_OVERRUN) {
		/* clear error interrupt */
		devpriv->write_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		dev_err(dev->class_dev, "overrun\n");
		return IRQ_HANDLED;
	}

	if (devpriv->current_transfer == isa_dma_transfer)
		labpc_handle_dma_status(dev);
	else
		labpc_drain_fifo(dev);

	if (devpriv->stat1 & STAT1_CNTINT) {
		dev_err(dev->class_dev, "handled timer interrupt?\n");
		/*  clear it */
		devpriv->write_byte(dev, 0x1, TIMER_CLEAR_REG);
	}

	if (devpriv->stat1 & STAT1_OVERFLOW) {
		/*  clear error interrupt */
		devpriv->write_byte(dev, 0x1, ADC_FIFO_CLEAR_REG);
		async->events |= COMEDI_CB_ERROR;
		comedi_handle_events(dev, s);
		dev_err(dev->class_dev, "overflow\n");
		return IRQ_HANDLED;
	}
	/*  handle external stop trigger */
	if (cmd->stop_src == TRIG_EXT) {
		if (devpriv->stat2 & STAT2_OUTA1) {
			labpc_drain_dregs(dev);
			async->events |= COMEDI_CB_EOA;
		}
	}

	/* TRIG_COUNT end of acquisition */
	if (cmd->stop_src == TRIG_COUNT) {
		if (devpriv->count == 0)
			async->events |= COMEDI_CB_EOA;
	}

	comedi_handle_events(dev, s);
	return IRQ_HANDLED;
}