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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct tee_device {int flags; TYPE_1__ dev; int /*<<< orphan*/ * pool; int /*<<< orphan*/  c_no_users; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int TEE_DEVICE_FLAG_REGISTERED ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tee_dev_group ; 
 int /*<<< orphan*/  tee_device_put (struct tee_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void tee_device_unregister(struct tee_device *teedev)
{
	if (!teedev)
		return;

	if (teedev->flags & TEE_DEVICE_FLAG_REGISTERED) {
		sysfs_remove_group(&teedev->dev.kobj, &tee_dev_group);
		cdev_del(&teedev->cdev);
		device_del(&teedev->dev);
	}

	tee_device_put(teedev);
	wait_for_completion(&teedev->c_no_users);

	/*
	 * No need to take a mutex any longer now since teedev->desc was
	 * set to NULL before teedev->c_no_users was completed.
	 */

	teedev->pool = NULL;

	put_device(&teedev->dev);
}