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
struct pci9118_private {int /*<<< orphan*/  ai_neverending; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct pci9118_private* private; } ;
struct comedi_cmd {scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 scalar_t__ PCI9118_AI_FIFO_REG ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 unsigned short inl (scalar_t__) ; 

__attribute__((used)) static void pci9118_ai_get_onesample(struct comedi_device *dev,
				     struct comedi_subdevice *s)
{
	struct pci9118_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned short sampl;

	sampl = inl(dev->iobase + PCI9118_AI_FIFO_REG);

	comedi_buf_write_samples(s, &sampl, 1);

	if (!devpriv->ai_neverending) {
		if (s->async->scans_done >= cmd->stop_arg)
			s->async->events |= COMEDI_CB_EOA;
	}
}