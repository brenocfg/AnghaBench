#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct ccw_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int (* alloc ) (struct ccw_device*) ;int (* set ) (struct ccw_device*,int) ;int /*<<< orphan*/  (* free ) (struct ccw_device*) ;int /*<<< orphan*/  attr_group; int /*<<< orphan*/  (* reset ) (struct ccw_device*) ;} ;

/* Variables and functions */
 TYPE_5__* cmbops ; 
 scalar_t__ cmf_enabled (struct ccw_device*) ; 
 int /*<<< orphan*/  device_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (TYPE_1__*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*) ; 
 int stub2 (struct ccw_device*) ; 
 int /*<<< orphan*/  stub3 (struct ccw_device*) ; 
 int /*<<< orphan*/  stub4 (struct ccw_device*) ; 
 int stub5 (struct ccw_device*,int) ; 
 int /*<<< orphan*/  stub6 (struct ccw_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int enable_cmf(struct ccw_device *cdev)
{
	int ret = 0;

	device_lock(&cdev->dev);
	if (cmf_enabled(cdev)) {
		cmbops->reset(cdev);
		goto out_unlock;
	}
	get_device(&cdev->dev);
	ret = cmbops->alloc(cdev);
	if (ret)
		goto out;
	cmbops->reset(cdev);
	ret = sysfs_create_group(&cdev->dev.kobj, cmbops->attr_group);
	if (ret) {
		cmbops->free(cdev);
		goto out;
	}
	ret = cmbops->set(cdev, 2);
	if (ret) {
		sysfs_remove_group(&cdev->dev.kobj, cmbops->attr_group);
		cmbops->free(cdev);
	}
out:
	if (ret)
		put_device(&cdev->dev);
out_unlock:
	device_unlock(&cdev->dev);
	return ret;
}