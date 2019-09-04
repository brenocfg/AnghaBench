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
struct comedi_subdevice {int type; } ;
struct comedi_device {unsigned int n_subdevices; int /*<<< orphan*/  attach_lock; struct comedi_subdevice* subdevices; scalar_t__ attached; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int comedi_find_subdevice_by_type(struct comedi_device *dev, int type,
				  unsigned int subd)
{
	struct comedi_subdevice *s;
	int ret = -ENODEV;

	down_read(&dev->attach_lock);
	if (dev->attached)
		for (; subd < dev->n_subdevices; subd++) {
			s = &dev->subdevices[subd];
			if (s->type == type) {
				ret = subd;
				break;
			}
		}
	up_read(&dev->attach_lock);
	return ret;
}