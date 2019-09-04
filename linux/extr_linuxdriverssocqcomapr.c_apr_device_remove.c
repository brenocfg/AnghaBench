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
struct device {scalar_t__ driver; } ;
struct apr_driver {int /*<<< orphan*/  (* remove ) (struct apr_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct apr_device {int /*<<< orphan*/  svc_id; TYPE_1__ dev; } ;
struct apr {int /*<<< orphan*/  svcs_lock; int /*<<< orphan*/  svcs_idr; } ;

/* Variables and functions */
 struct apr* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct apr_device*) ; 
 struct apr_device* to_apr_device (struct device*) ; 
 struct apr_driver* to_apr_driver (scalar_t__) ; 

__attribute__((used)) static int apr_device_remove(struct device *dev)
{
	struct apr_device *adev = to_apr_device(dev);
	struct apr_driver *adrv;
	struct apr *apr = dev_get_drvdata(adev->dev.parent);

	if (dev->driver) {
		adrv = to_apr_driver(dev->driver);
		if (adrv->remove)
			adrv->remove(adev);
		spin_lock(&apr->svcs_lock);
		idr_remove(&apr->svcs_idr, adev->svc_id);
		spin_unlock(&apr->svcs_lock);
	}

	return 0;
}