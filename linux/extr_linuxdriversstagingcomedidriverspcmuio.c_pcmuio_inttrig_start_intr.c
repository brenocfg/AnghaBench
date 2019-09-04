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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmuio_private* private; } ;
struct comedi_cmd {unsigned int start_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pcmuio_start_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcmuio_inttrig_start_intr(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned int trig_num)
{
	struct pcmuio_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	unsigned long flags;

	if (trig_num != cmd->start_arg)
		return -EINVAL;

	spin_lock_irqsave(&chip->spinlock, flags);
	s->async->inttrig = NULL;
	if (chip->active)
		pcmuio_start_intr(dev, s);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	return 1;
}