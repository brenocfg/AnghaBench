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
struct pci1710_private {int max_samples; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct pci1710_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int /*<<< orphan*/  events; int /*<<< orphan*/  cur_chan; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ PCI171X_CLRINT_REG ; 
 unsigned int PCI171X_STATUS_FF ; 
 unsigned int PCI171X_STATUS_FH ; 
 scalar_t__ PCI171X_STATUS_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int pci1710_ai_read_sample (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pci1710_handle_fifo(struct comedi_device *dev,
				struct comedi_subdevice *s)
{
	struct pci1710_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int status;
	int i;

	status = inw(dev->iobase + PCI171X_STATUS_REG);
	if (!(status & PCI171X_STATUS_FH)) {
		dev_dbg(dev->class_dev, "A/D FIFO not half full!\n");
		async->events |= COMEDI_CB_ERROR;
		return;
	}
	if (status & PCI171X_STATUS_FF) {
		dev_dbg(dev->class_dev,
			"A/D FIFO Full status (Fatal Error!)\n");
		async->events |= COMEDI_CB_ERROR;
		return;
	}

	for (i = 0; i < devpriv->max_samples; i++) {
		unsigned int val;
		int ret;

		ret = pci1710_ai_read_sample(dev, s, s->async->cur_chan, &val);
		if (ret) {
			s->async->events |= COMEDI_CB_ERROR;
			break;
		}

		if (!comedi_buf_write_samples(s, &val, 1))
			break;

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg) {
			async->events |= COMEDI_CB_EOA;
			break;
		}
	}

	outb(0, dev->iobase + PCI171X_CLRINT_REG);
}