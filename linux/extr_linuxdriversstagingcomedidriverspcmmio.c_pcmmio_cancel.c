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
struct pcmmio_private {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pcmmio_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmmio_stop_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcmmio_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcmmio_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->spinlock, flags);
	if (devpriv->active)
		pcmmio_stop_intr(dev, s);
	spin_unlock_irqrestore(&devpriv->spinlock, flags);

	return 0;
}