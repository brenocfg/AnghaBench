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
struct inode {int dummy; } ;
struct file {struct comedi_file* private_data; } ;
struct comedi_subdevice {struct file* lock; struct file* busy; } ;
struct comedi_file {struct comedi_device* dev; } ;
struct comedi_device {int n_subdevices; int use_count; int /*<<< orphan*/  mutex; TYPE_1__* driver; int /*<<< orphan*/  (* close ) (struct comedi_device*) ;scalar_t__ attached; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 int /*<<< orphan*/  do_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  kfree (struct comedi_file*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 

__attribute__((used)) static int comedi_close(struct inode *inode, struct file *file)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_device *dev = cfp->dev;
	struct comedi_subdevice *s = NULL;
	int i;

	mutex_lock(&dev->mutex);

	if (dev->subdevices) {
		for (i = 0; i < dev->n_subdevices; i++) {
			s = &dev->subdevices[i];

			if (s->busy == file)
				do_cancel(dev, s);
			if (s->lock == file)
				s->lock = NULL;
		}
	}
	if (dev->attached && dev->use_count == 1) {
		if (dev->close)
			dev->close(dev);
		module_put(dev->driver->module);
	}

	dev->use_count--;

	mutex_unlock(&dev->mutex);
	comedi_dev_put(dev);
	kfree(cfp);

	return 0;
}