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
struct tape_class_device {TYPE_1__* char_device; int /*<<< orphan*/  mode_name; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct tape_class_device*) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tape_class_device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_class ; 

void unregister_tape_dev(struct device *device, struct tape_class_device *tcd)
{
	if (tcd != NULL && !IS_ERR(tcd)) {
		sysfs_remove_link(&device->kobj, tcd->mode_name);
		device_destroy(tape_class, tcd->char_device->dev);
		cdev_del(tcd->char_device);
		kfree(tcd);
	}
}