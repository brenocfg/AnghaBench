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
struct tty_driver {unsigned int num; scalar_t__ type; int flags; struct ktermios** termios; int /*<<< orphan*/  name; int /*<<< orphan*/  minor_start; int /*<<< orphan*/  major; } ;
struct ktermios {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; struct attribute_group const** groups; int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/  class; scalar_t__ devt; } ;
struct attribute_group {int dummy; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TTY_DRIVER_DYNAMIC_ALLOC ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,void*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (struct device*,int) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ktermios*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pty_line_name (struct tty_driver*,unsigned int,char*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int tty_cdev_add (struct tty_driver*,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  tty_class ; 
 int /*<<< orphan*/  tty_device_create_release ; 
 int /*<<< orphan*/  tty_line_name (struct tty_driver*,unsigned int,char*) ; 

struct device *tty_register_device_attr(struct tty_driver *driver,
				   unsigned index, struct device *device,
				   void *drvdata,
				   const struct attribute_group **attr_grp)
{
	char name[64];
	dev_t devt = MKDEV(driver->major, driver->minor_start) + index;
	struct ktermios *tp;
	struct device *dev;
	int retval;

	if (index >= driver->num) {
		pr_err("%s: Attempt to register invalid tty line number (%d)\n",
		       driver->name, index);
		return ERR_PTR(-EINVAL);
	}

	if (driver->type == TTY_DRIVER_TYPE_PTY)
		pty_line_name(driver, index, name);
	else
		tty_line_name(driver, index, name);

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->devt = devt;
	dev->class = tty_class;
	dev->parent = device;
	dev->release = tty_device_create_release;
	dev_set_name(dev, "%s", name);
	dev->groups = attr_grp;
	dev_set_drvdata(dev, drvdata);

	dev_set_uevent_suppress(dev, 1);

	retval = device_register(dev);
	if (retval)
		goto err_put;

	if (!(driver->flags & TTY_DRIVER_DYNAMIC_ALLOC)) {
		/*
		 * Free any saved termios data so that the termios state is
		 * reset when reusing a minor number.
		 */
		tp = driver->termios[index];
		if (tp) {
			driver->termios[index] = NULL;
			kfree(tp);
		}

		retval = tty_cdev_add(driver, devt, index, 1);
		if (retval)
			goto err_del;
	}

	dev_set_uevent_suppress(dev, 0);
	kobject_uevent(&dev->kobj, KOBJ_ADD);

	return dev;

err_del:
	device_del(dev);
err_put:
	put_device(dev);

	return ERR_PTR(retval);
}