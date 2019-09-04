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
struct device {int dummy; } ;
struct ccw_device {TYPE_1__* drv; scalar_t__ online; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (struct ccw_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static void ccw_device_pm_complete(struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);

	if (cdev->online && cdev->drv && cdev->drv->complete)
		cdev->drv->complete(cdev);
}