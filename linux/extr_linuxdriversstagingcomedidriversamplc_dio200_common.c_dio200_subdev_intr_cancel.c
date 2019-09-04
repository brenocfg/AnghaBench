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
struct dio200_subdev_intr {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;
struct comedi_subdevice {struct dio200_subdev_intr* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio200_stop_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dio200_subdev_intr_cancel(struct comedi_device *dev,
				     struct comedi_subdevice *s)
{
	struct dio200_subdev_intr *subpriv = s->private;
	unsigned long flags;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	if (subpriv->active)
		dio200_stop_intr(dev, s);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	return 0;
}