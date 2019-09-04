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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pcmuio_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmuio_stop_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcmuio_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcmuio_private *devpriv = dev->private;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	unsigned long flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	if (chip->active)
		pcmuio_stop_intr(dev, s);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	return 0;
}