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
struct device {int dummy; } ;
struct comedi_subdevice {unsigned int minor; struct device* class_dev; int /*<<< orphan*/  index; struct comedi_device* device; } ;
struct comedi_device {int /*<<< orphan*/  minor; int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 scalar_t__ COMEDI_NUM_BOARD_MINORS ; 
 unsigned int COMEDI_NUM_SUBDEVICE_MINORS ; 
 int EBUSY ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  comedi_class ; 
 struct comedi_subdevice** comedi_subdevice_minor_table ; 
 int /*<<< orphan*/  comedi_subdevice_minor_table_lock ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int comedi_alloc_subdevice_minor(struct comedi_subdevice *s)
{
	struct comedi_device *dev = s->device;
	struct device *csdev;
	unsigned int i;

	mutex_lock(&comedi_subdevice_minor_table_lock);
	for (i = 0; i < COMEDI_NUM_SUBDEVICE_MINORS; ++i) {
		if (!comedi_subdevice_minor_table[i]) {
			comedi_subdevice_minor_table[i] = s;
			break;
		}
	}
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	if (i == COMEDI_NUM_SUBDEVICE_MINORS) {
		dev_err(dev->class_dev,
			"ran out of minor numbers for subdevice files\n");
		return -EBUSY;
	}
	i += COMEDI_NUM_BOARD_MINORS;
	s->minor = i;
	csdev = device_create(comedi_class, dev->class_dev,
			      MKDEV(COMEDI_MAJOR, i), NULL, "comedi%i_subd%i",
			      dev->minor, s->index);
	if (!IS_ERR(csdev))
		s->class_dev = csdev;

	return 0;
}