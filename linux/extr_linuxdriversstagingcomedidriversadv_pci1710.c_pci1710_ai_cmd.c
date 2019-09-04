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
struct pci1710_private {int ctrl; int ctrl_ext; int ai_et; int /*<<< orphan*/  saved_seglen; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pci1710_private* private; } ;
struct comedi_cmd {int flags; scalar_t__ convert_src; scalar_t__ start_src; int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WAKE_EOS ; 
 scalar_t__ PCI171X_CLRFIFO_REG ; 
 scalar_t__ PCI171X_CLRINT_REG ; 
 int PCI171X_CTRL_CNT0 ; 
 int PCI171X_CTRL_EXT ; 
 int PCI171X_CTRL_GATE ; 
 int PCI171X_CTRL_IRQEN ; 
 int PCI171X_CTRL_ONEFH ; 
 int PCI171X_CTRL_PACER ; 
 scalar_t__ PCI171X_CTRL_REG ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci1710_ai_setup_chanlist (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci1710_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pci1710_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;

	pci1710_ai_setup_chanlist(dev, s, cmd->chanlist, cmd->chanlist_len,
				  devpriv->saved_seglen);

	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	devpriv->ctrl &= PCI171X_CTRL_CNT0;
	if ((cmd->flags & CMDF_WAKE_EOS) == 0)
		devpriv->ctrl |= PCI171X_CTRL_ONEFH;

	if (cmd->convert_src == TRIG_TIMER) {
		comedi_8254_update_divisors(dev->pacer);

		devpriv->ctrl |= PCI171X_CTRL_PACER | PCI171X_CTRL_IRQEN;
		if (cmd->start_src == TRIG_EXT) {
			devpriv->ctrl_ext = devpriv->ctrl;
			devpriv->ctrl &= ~(PCI171X_CTRL_PACER |
					   PCI171X_CTRL_ONEFH |
					   PCI171X_CTRL_GATE);
			devpriv->ctrl |= PCI171X_CTRL_EXT;
			devpriv->ai_et = 1;
		} else {	/* TRIG_NOW */
			devpriv->ai_et = 0;
		}
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

		if (cmd->start_src == TRIG_NOW)
			comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	} else {	/* TRIG_EXT */
		devpriv->ctrl |= PCI171X_CTRL_EXT | PCI171X_CTRL_IRQEN;
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
	}

	return 0;
}