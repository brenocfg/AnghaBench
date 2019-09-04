#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scm_driver {int /*<<< orphan*/  (* notify ) (struct scm_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {scalar_t__ rank; scalar_t__ oper_state; } ;
struct scm_device {TYPE_2__ dev; TYPE_1__ attrs; } ;
struct sale {scalar_t__ rank; scalar_t__ op_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  SCM_CHANGE ; 
 int /*<<< orphan*/  device_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scm_device*,int /*<<< orphan*/ ) ; 
 struct scm_driver* to_scm_drv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scmdev_update(struct scm_device *scmdev, struct sale *sale)
{
	struct scm_driver *scmdrv;
	bool changed;

	device_lock(&scmdev->dev);
	changed = scmdev->attrs.rank != sale->rank ||
		  scmdev->attrs.oper_state != sale->op_state;
	scmdev->attrs.rank = sale->rank;
	scmdev->attrs.oper_state = sale->op_state;
	if (!scmdev->dev.driver)
		goto out;
	scmdrv = to_scm_drv(scmdev->dev.driver);
	if (changed && scmdrv->notify)
		scmdrv->notify(scmdev, SCM_CHANGE);
out:
	device_unlock(&scmdev->dev);
	if (changed)
		kobject_uevent(&scmdev->dev.kobj, KOBJ_CHANGE);
}