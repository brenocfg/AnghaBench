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
typedef  int u32 ;
struct hpdi_private {scalar_t__ dio_count; scalar_t__ plx9080_mmio; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  spinlock; scalar_t__ mmio; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct hpdi_private* private; } ;
struct comedi_async {int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BOARD_STATUS_REG ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ INTERRUPT_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PLX_DMACSR_CLEARINTR ; 
 int PLX_DMACSR_ENABLE ; 
 int PLX_INTCSR_DMA0IA ; 
 int PLX_INTCSR_DMA1IA ; 
 int PLX_INTCSR_LDBIA ; 
 int PLX_INTCSR_PLIA ; 
 scalar_t__ PLX_REG_DMACSR0 ; 
 scalar_t__ PLX_REG_DMACSR1 ; 
 scalar_t__ PLX_REG_INTCSR ; 
 scalar_t__ PLX_REG_L2PDBELL ; 
 int RX_OVERRUN_BIT ; 
 int RX_UNDERRUN_BIT ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gsc_hpdi_drain_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t gsc_hpdi_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct hpdi_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	u32 hpdi_intr_status, hpdi_board_status;
	u32 plx_status;
	u32 plx_bits;
	u8 dma0_status, dma1_status;
	unsigned long flags;

	if (!dev->attached)
		return IRQ_NONE;

	plx_status = readl(devpriv->plx9080_mmio + PLX_REG_INTCSR);
	if ((plx_status &
	     (PLX_INTCSR_DMA0IA | PLX_INTCSR_DMA1IA | PLX_INTCSR_PLIA)) == 0)
		return IRQ_NONE;

	hpdi_intr_status = readl(dev->mmio + INTERRUPT_STATUS_REG);
	hpdi_board_status = readl(dev->mmio + BOARD_STATUS_REG);

	if (hpdi_intr_status)
		writel(hpdi_intr_status, dev->mmio + INTERRUPT_STATUS_REG);

	/* spin lock makes sure no one else changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma0_status = readb(devpriv->plx9080_mmio + PLX_REG_DMACSR0);
	if (plx_status & PLX_INTCSR_DMA0IA) {
		/* dma chan 0 interrupt */
		writeb((dma0_status & PLX_DMACSR_ENABLE) | PLX_DMACSR_CLEARINTR,
		       devpriv->plx9080_mmio + PLX_REG_DMACSR0);

		if (dma0_status & PLX_DMACSR_ENABLE)
			gsc_hpdi_drain_dma(dev, 0);
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* spin lock makes sure no one else changes plx dma control reg */
	spin_lock_irqsave(&dev->spinlock, flags);
	dma1_status = readb(devpriv->plx9080_mmio + PLX_REG_DMACSR1);
	if (plx_status & PLX_INTCSR_DMA1IA) {
		/* XXX */ /* dma chan 1 interrupt */
		writeb((dma1_status & PLX_DMACSR_ENABLE) | PLX_DMACSR_CLEARINTR,
		       devpriv->plx9080_mmio + PLX_REG_DMACSR1);
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* clear possible plx9080 interrupt sources */
	if (plx_status & PLX_INTCSR_LDBIA) {
		/* clear local doorbell interrupt */
		plx_bits = readl(devpriv->plx9080_mmio + PLX_REG_L2PDBELL);
		writel(plx_bits, devpriv->plx9080_mmio + PLX_REG_L2PDBELL);
	}

	if (hpdi_board_status & RX_OVERRUN_BIT) {
		dev_err(dev->class_dev, "rx fifo overrun\n");
		async->events |= COMEDI_CB_ERROR;
	}

	if (hpdi_board_status & RX_UNDERRUN_BIT) {
		dev_err(dev->class_dev, "rx fifo underrun\n");
		async->events |= COMEDI_CB_ERROR;
	}

	if (devpriv->dio_count == 0)
		async->events |= COMEDI_CB_EOA;

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}