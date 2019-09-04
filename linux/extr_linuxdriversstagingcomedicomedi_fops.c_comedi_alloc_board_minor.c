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
struct comedi_device {unsigned int minor; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct comedi_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 struct comedi_device** comedi_board_minor_table ; 
 int /*<<< orphan*/  comedi_board_minor_table_lock ; 
 int /*<<< orphan*/  comedi_class ; 
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_device_cleanup (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_device_init (struct comedi_device*) ; 
 unsigned int comedi_num_legacy_minors ; 
 int /*<<< orphan*/  comedi_set_hw_dev (struct comedi_device*,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct comedi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct comedi_device *comedi_alloc_board_minor(struct device *hardware_device)
{
	struct comedi_device *dev;
	struct device *csdev;
	unsigned int i;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);
	comedi_device_init(dev);
	comedi_set_hw_dev(dev, hardware_device);
	mutex_lock(&dev->mutex);
	mutex_lock(&comedi_board_minor_table_lock);
	for (i = hardware_device ? comedi_num_legacy_minors : 0;
	     i < COMEDI_NUM_BOARD_MINORS; ++i) {
		if (!comedi_board_minor_table[i]) {
			comedi_board_minor_table[i] = dev;
			break;
		}
	}
	mutex_unlock(&comedi_board_minor_table_lock);
	if (i == COMEDI_NUM_BOARD_MINORS) {
		mutex_unlock(&dev->mutex);
		comedi_device_cleanup(dev);
		comedi_dev_put(dev);
		dev_err(hardware_device,
			"ran out of minor numbers for board device files\n");
		return ERR_PTR(-EBUSY);
	}
	dev->minor = i;
	csdev = device_create(comedi_class, hardware_device,
			      MKDEV(COMEDI_MAJOR, i), NULL, "comedi%i", i);
	if (!IS_ERR(csdev))
		dev->class_dev = get_device(csdev);

	/* Note: dev->mutex needs to be unlocked by the caller. */
	return dev;
}