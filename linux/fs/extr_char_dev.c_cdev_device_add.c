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
struct device {scalar_t__ devt; int /*<<< orphan*/  kobj; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int cdev_add (struct cdev*,scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (struct cdev*) ; 
 int /*<<< orphan*/  cdev_set_parent (struct cdev*,int /*<<< orphan*/ *) ; 
 int device_add (struct device*) ; 

int cdev_device_add(struct cdev *cdev, struct device *dev)
{
	int rc = 0;

	if (dev->devt) {
		cdev_set_parent(cdev, &dev->kobj);

		rc = cdev_add(cdev, dev->devt, 1);
		if (rc)
			return rc;
	}

	rc = device_add(dev);
	if (rc)
		cdev_del(cdev);

	return rc;
}