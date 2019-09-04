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
struct nidio96_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ di_mite_chan; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ mmio; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct nidio96_private* private; } ;
struct comedi_async {int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int ClearExpired ; 
 int ClearPrimaryTC ; 
 int ClearSecondaryTC ; 
 int ClearWaited ; 
 int CountExpired ; 
 int DataLeft ; 
 scalar_t__ Group_1_FIFO ; 
 scalar_t__ Group_1_First_Clear ; 
 scalar_t__ Group_1_Flags ; 
 scalar_t__ Group_1_Second_Clear ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IntEn ; 
 scalar_t__ Interrupt_And_Window_Status ; 
 scalar_t__ Master_DMA_And_Interrupt_Control ; 
 scalar_t__ OpMode ; 
 int PrimaryTC ; 
 int SecondaryTC ; 
 int TransferReady ; 
 int Waited ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mite_ack_linkc (scalar_t__,struct comedi_subdevice*,int) ; 
 int readb (scalar_t__) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t nidio_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct nidio96_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async = s->async;
	unsigned int auxdata;
	int flags;
	int status;
	int work = 0;

	/* interrupcions parasites */
	if (!dev->attached) {
		/* assume it's from another card */
		return IRQ_NONE;
	}

	/* Lock to avoid race with comedi_poll */
	spin_lock(&dev->spinlock);

	status = readb(dev->mmio + Interrupt_And_Window_Status);
	flags = readb(dev->mmio + Group_1_Flags);

	spin_lock(&devpriv->mite_channel_lock);
	if (devpriv->di_mite_chan) {
		mite_ack_linkc(devpriv->di_mite_chan, s, false);
		/* XXX need to byteswap sync'ed dma */
	}
	spin_unlock(&devpriv->mite_channel_lock);

	while (status & DataLeft) {
		work++;
		if (work > 20) {
			dev_dbg(dev->class_dev, "too much work in interrupt\n");
			writeb(0x00,
			       dev->mmio + Master_DMA_And_Interrupt_Control);
			break;
		}

		flags &= IntEn;

		if (flags & TransferReady) {
			while (flags & TransferReady) {
				work++;
				if (work > 100) {
					dev_dbg(dev->class_dev,
						"too much work in interrupt\n");
					writeb(0x00, dev->mmio +
					       Master_DMA_And_Interrupt_Control
					      );
					goto out;
				}
				auxdata = readl(dev->mmio + Group_1_FIFO);
				comedi_buf_write_samples(s, &auxdata, 1);
				flags = readb(dev->mmio + Group_1_Flags);
			}
		}

		if (flags & CountExpired) {
			writeb(ClearExpired, dev->mmio + Group_1_Second_Clear);
			async->events |= COMEDI_CB_EOA;

			writeb(0x00, dev->mmio + OpMode);
			break;
		} else if (flags & Waited) {
			writeb(ClearWaited, dev->mmio + Group_1_First_Clear);
			async->events |= COMEDI_CB_ERROR;
			break;
		} else if (flags & PrimaryTC) {
			writeb(ClearPrimaryTC,
			       dev->mmio + Group_1_First_Clear);
			async->events |= COMEDI_CB_EOA;
		} else if (flags & SecondaryTC) {
			writeb(ClearSecondaryTC,
			       dev->mmio + Group_1_First_Clear);
			async->events |= COMEDI_CB_EOA;
		}

		flags = readb(dev->mmio + Group_1_Flags);
		status = readb(dev->mmio + Interrupt_And_Window_Status);
	}

out:
	comedi_handle_events(dev, s);
#if 0
	if (!tag)
		writeb(0x03, dev->mmio + Master_DMA_And_Interrupt_Control);
#endif

	spin_unlock(&dev->spinlock);
	return IRQ_HANDLED;
}