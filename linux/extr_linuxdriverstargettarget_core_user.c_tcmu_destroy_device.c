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
struct tcmu_dev {int /*<<< orphan*/  kref; int /*<<< orphan*/  uio_info; int /*<<< orphan*/  node; int /*<<< orphan*/  qfull_timer; int /*<<< orphan*/  cmd_timer; } ;
struct se_device {int dummy; } ;

/* Variables and functions */
 struct tcmu_dev* TCMU_DEV (struct se_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_udev_mutex ; 
 int /*<<< orphan*/  tcmu_dev_kref_release ; 
 int /*<<< orphan*/  tcmu_send_dev_remove_event (struct tcmu_dev*) ; 
 int /*<<< orphan*/  uio_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcmu_destroy_device(struct se_device *dev)
{
	struct tcmu_dev *udev = TCMU_DEV(dev);

	del_timer_sync(&udev->cmd_timer);
	del_timer_sync(&udev->qfull_timer);

	mutex_lock(&root_udev_mutex);
	list_del(&udev->node);
	mutex_unlock(&root_udev_mutex);

	tcmu_send_dev_remove_event(udev);

	uio_unregister_device(&udev->uio_info);

	/* release ref from configure */
	kref_put(&udev->kref, tcmu_dev_kref_release);
}