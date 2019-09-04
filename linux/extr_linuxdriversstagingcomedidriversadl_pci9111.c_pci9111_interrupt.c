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
struct pci9111_private_data {scalar_t__ lcr_io_base; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct pci9111_private_data* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCI9111_AI_RANGE_STAT_REG ; 
 unsigned int PCI9111_AI_STAT_FF_FF ; 
 unsigned int PCI9111_AI_STAT_FF_HF ; 
 scalar_t__ PCI9111_INT_CLR_REG ; 
 unsigned char PCI9111_LI1_ACTIVE ; 
 unsigned char PCI9111_LI2_ACTIVE ; 
 scalar_t__ PLX9052_INTCSR ; 
 unsigned char PLX9052_INTCSR_PCIENAB ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 void* inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci9111_handle_fifo_half_full (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pci9111_interrupt(int irq, void *p_device)
{
	struct comedi_device *dev = p_device;
	struct pci9111_private_data *dev_private = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_async *async;
	struct comedi_cmd *cmd;
	unsigned int status;
	unsigned long irq_flags;
	unsigned char intcsr;

	if (!dev->attached) {
		/*  Ignore interrupt before device fully attached. */
		/*  Might not even have allocated subdevices yet! */
		return IRQ_NONE;
	}

	async = s->async;
	cmd = &async->cmd;

	spin_lock_irqsave(&dev->spinlock, irq_flags);

	/*  Check if we are source of interrupt */
	intcsr = inb(dev_private->lcr_io_base + PLX9052_INTCSR);
	if (!(((intcsr & PLX9052_INTCSR_PCIENAB) != 0) &&
	      (((intcsr & PCI9111_LI1_ACTIVE) == PCI9111_LI1_ACTIVE) ||
	       ((intcsr & PCI9111_LI2_ACTIVE) == PCI9111_LI2_ACTIVE)))) {
		/*  Not the source of the interrupt. */
		/*  (N.B. not using PLX9052_INTCSR_SOFTINT) */
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
		return IRQ_NONE;
	}

	if ((intcsr & PCI9111_LI1_ACTIVE) == PCI9111_LI1_ACTIVE) {
		/*  Interrupt comes from fifo_half-full signal */

		status = inb(dev->iobase + PCI9111_AI_RANGE_STAT_REG);

		/* '0' means FIFO is full, data may have been lost */
		if (!(status & PCI9111_AI_STAT_FF_FF)) {
			spin_unlock_irqrestore(&dev->spinlock, irq_flags);
			dev_dbg(dev->class_dev, "fifo overflow\n");
			outb(0, dev->iobase + PCI9111_INT_CLR_REG);
			async->events |= COMEDI_CB_ERROR;
			comedi_handle_events(dev, s);

			return IRQ_HANDLED;
		}

		/* '0' means FIFO is half-full */
		if (!(status & PCI9111_AI_STAT_FF_HF))
			pci9111_handle_fifo_half_full(dev, s);
	}

	if (cmd->stop_src == TRIG_COUNT && async->scans_done >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	outb(0, dev->iobase + PCI9111_INT_CLR_REG);

	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}