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
struct pcmmio_private {int active; int /*<<< orphan*/  spinlock; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmmio_private* private; } ;
struct comedi_cmd {scalar_t__ start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_INT ; 
 int /*<<< orphan*/  pcmmio_inttrig_start_intr ; 
 int /*<<< orphan*/  pcmmio_start_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcmmio_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcmmio_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->spinlock, flags);
	devpriv->active = 1;

	/* Set up start of acquisition. */
	if (cmd->start_src == TRIG_INT)
		s->async->inttrig = pcmmio_inttrig_start_intr;
	else	/* TRIG_NOW */
		pcmmio_start_intr(dev, s);

	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	return 0;
}