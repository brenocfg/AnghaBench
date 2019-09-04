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
typedef  int u8 ;
struct pcidas64_private {scalar_t__ plx9080_iobase; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct comedi_subdevice* write_subdev; struct pcidas64_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 unsigned short DAC_DONE_BIT ; 
 int PLX_DMACSR_CLEARINTR ; 
 int PLX_DMACSR_DONE ; 
 int PLX_DMACSR_ENABLE ; 
 unsigned int PLX_INTCSR_DMA0IA ; 
 scalar_t__ PLX_REG_DMACSR0 ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ ao_dma_needs_restart (struct comedi_device*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 scalar_t__ last_ao_dma_load_completed (struct comedi_device*) ; 
 int /*<<< orphan*/  load_ao_dma (struct comedi_device*,struct comedi_cmd*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  restart_ao_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void handle_ao_interrupt(struct comedi_device *dev,
				unsigned short status, unsigned int plx_status)
{
	struct pcidas64_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->write_subdev;
	struct comedi_async *async;
	struct comedi_cmd *cmd;
	u8 dma0_status;
	unsigned long flags;

	/* board might not support ao, in which case write_subdev is NULL */
	if (!s)
		return;
	async = s->async;
	cmd = &async->cmd;

	/* spin lock makes sure no one else changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma0_status = readb(devpriv->plx9080_iobase + PLX_REG_DMACSR0);
	if (plx_status & PLX_INTCSR_DMA0IA) {	/*  dma chan 0 interrupt */
		if ((dma0_status & PLX_DMACSR_ENABLE) &&
		    !(dma0_status & PLX_DMACSR_DONE)) {
			writeb(PLX_DMACSR_ENABLE | PLX_DMACSR_CLEARINTR,
			       devpriv->plx9080_iobase + PLX_REG_DMACSR0);
		} else {
			writeb(PLX_DMACSR_CLEARINTR,
			       devpriv->plx9080_iobase + PLX_REG_DMACSR0);
		}
		spin_unlock_irqrestore(&dev->spinlock, flags);
		if (dma0_status & PLX_DMACSR_ENABLE) {
			load_ao_dma(dev, cmd);
			/* try to recover from dma end-of-chain event */
			if (ao_dma_needs_restart(dev, dma0_status))
				restart_ao_dma(dev);
		}
	} else {
		spin_unlock_irqrestore(&dev->spinlock, flags);
	}

	if ((status & DAC_DONE_BIT)) {
		if ((cmd->stop_src == TRIG_COUNT &&
		     async->scans_done >= cmd->stop_arg) ||
		    last_ao_dma_load_completed(dev))
			async->events |= COMEDI_CB_EOA;
		else
			async->events |= COMEDI_CB_ERROR;
	}
	comedi_handle_events(dev, s);
}