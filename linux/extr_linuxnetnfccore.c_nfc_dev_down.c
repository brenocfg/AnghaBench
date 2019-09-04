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
struct nfc_dev {int dev_up; int /*<<< orphan*/  dev; TYPE_1__* ops; scalar_t__ active_target; scalar_t__ polling; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dev_down ) (struct nfc_dev*) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfc_dev*) ; 

int nfc_dev_down(struct nfc_dev *dev)
{
	int rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->dev_up) {
		rc = -EALREADY;
		goto error;
	}

	if (dev->polling || dev->active_target) {
		rc = -EBUSY;
		goto error;
	}

	if (dev->ops->dev_down)
		dev->ops->dev_down(dev);

	dev->dev_up = false;

error:
	device_unlock(&dev->dev);
	return rc;
}