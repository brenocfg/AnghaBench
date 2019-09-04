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
struct pci230_private {int ao_cmd_started; int hwver; unsigned short daccon; int /*<<< orphan*/  isr_spinlock; int /*<<< orphan*/  ier; scalar_t__ daqio; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; struct pci230_private* private; } ;
struct comedi_cmd {int scan_begin_src; int scan_begin_arg; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CR_INVERT ; 
 int /*<<< orphan*/  GAT_VCC ; 
 unsigned short PCI230P2_DAC_TRIG_EXTN ; 
 unsigned short PCI230P2_DAC_TRIG_EXTP ; 
 unsigned short PCI230P2_DAC_TRIG_MASK ; 
 unsigned short PCI230P2_DAC_TRIG_NONE ; 
 unsigned short PCI230P2_DAC_TRIG_SW ; 
 unsigned short PCI230P2_DAC_TRIG_Z2CT1 ; 
 int /*<<< orphan*/  PCI230P2_INT_DAC ; 
 scalar_t__ PCI230_DACCON ; 
 scalar_t__ PCI230_INT_SCE ; 
 int /*<<< orphan*/  PCI230_INT_ZCLK_CT1 ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
#define  TRIG_EXT 130 
#define  TRIG_INT 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_inttrig_scan_begin ; 
 int /*<<< orphan*/  pci230_gat_config (int,int /*<<< orphan*/ ) ; 
 int pci230_handle_ao_fifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pci230_ao_start(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct pci230_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned long irqflags;

	devpriv->ao_cmd_started = true;

	if (devpriv->hwver >= 2) {
		/* Using DAC FIFO. */
		unsigned short scantrig;
		bool run;

		/* Preload FIFO data. */
		run = pci230_handle_ao_fifo(dev, s);
		comedi_handle_events(dev, s);
		if (!run) {
			/* Stopped. */
			return;
		}
		/* Set scan trigger source. */
		switch (cmd->scan_begin_src) {
		case TRIG_TIMER:
			scantrig = PCI230P2_DAC_TRIG_Z2CT1;
			break;
		case TRIG_EXT:
			/* Trigger on EXTTRIG/EXTCONVCLK pin. */
			if ((cmd->scan_begin_arg & CR_INVERT) == 0) {
				/* +ve edge */
				scantrig = PCI230P2_DAC_TRIG_EXTP;
			} else {
				/* -ve edge */
				scantrig = PCI230P2_DAC_TRIG_EXTN;
			}
			break;
		case TRIG_INT:
			scantrig = PCI230P2_DAC_TRIG_SW;
			break;
		default:
			/* Shouldn't get here. */
			scantrig = PCI230P2_DAC_TRIG_NONE;
			break;
		}
		devpriv->daccon =
		    (devpriv->daccon & ~PCI230P2_DAC_TRIG_MASK) | scantrig;
		outw(devpriv->daccon, devpriv->daqio + PCI230_DACCON);
	}
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		if (devpriv->hwver < 2) {
			/* Not using DAC FIFO. */
			/* Enable CT1 timer interrupt. */
			spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
			devpriv->ier |= PCI230_INT_ZCLK_CT1;
			outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
			spin_unlock_irqrestore(&devpriv->isr_spinlock,
					       irqflags);
		}
		/* Set CT1 gate high to start counting. */
		outb(pci230_gat_config(1, GAT_VCC),
		     dev->iobase + PCI230_ZGAT_SCE);
		break;
	case TRIG_INT:
		async->inttrig = pci230_ao_inttrig_scan_begin;
		break;
	}
	if (devpriv->hwver >= 2) {
		/* Using DAC FIFO.  Enable DAC FIFO interrupt. */
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
		devpriv->ier |= PCI230P2_INT_DAC;
		outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
	}
}