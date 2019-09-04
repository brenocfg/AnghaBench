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
struct comedi_subdevice {void* lock; scalar_t__ busy; } ;
struct comedi_device {unsigned long n_subdevices; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 

__attribute__((used)) static int do_unlock_ioctl(struct comedi_device *dev, unsigned long arg,
			   void *file)
{
	struct comedi_subdevice *s;

	if (arg >= dev->n_subdevices)
		return -EINVAL;
	s = &dev->subdevices[arg];

	if (s->busy)
		return -EBUSY;

	if (s->lock && s->lock != file)
		return -EACCES;

	if (s->lock == file)
		s->lock = NULL;

	return 0;
}