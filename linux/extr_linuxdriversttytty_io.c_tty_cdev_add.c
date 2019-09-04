#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_driver {TYPE_1__** cdevs; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* cdev_alloc () ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_fops ; 

__attribute__((used)) static int tty_cdev_add(struct tty_driver *driver, dev_t dev,
		unsigned int index, unsigned int count)
{
	int err;

	/* init here, since reused cdevs cause crashes */
	driver->cdevs[index] = cdev_alloc();
	if (!driver->cdevs[index])
		return -ENOMEM;
	driver->cdevs[index]->ops = &tty_fops;
	driver->cdevs[index]->owner = driver->owner;
	err = cdev_add(driver->cdevs[index], dev, count);
	if (err)
		kobject_put(&driver->cdevs[index]->kobj);
	return err;
}