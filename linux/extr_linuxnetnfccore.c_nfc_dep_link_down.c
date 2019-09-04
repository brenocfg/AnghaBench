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
struct nfc_dev {int dep_link_up; int /*<<< orphan*/  dev; int /*<<< orphan*/  rf_mode; int /*<<< orphan*/ * active_target; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dep_link_down ) (struct nfc_dev*) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFC_RF_NONE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_genl_dep_link_down_event (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_llcp_mac_is_down (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfc_dev*) ; 

int nfc_dep_link_down(struct nfc_dev *dev)
{
	int rc = 0;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	if (!dev->ops->dep_link_down)
		return -EOPNOTSUPP;

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->dep_link_up == false) {
		rc = -EALREADY;
		goto error;
	}

	rc = dev->ops->dep_link_down(dev);
	if (!rc) {
		dev->dep_link_up = false;
		dev->active_target = NULL;
		dev->rf_mode = NFC_RF_NONE;
		nfc_llcp_mac_is_down(dev);
		nfc_genl_dep_link_down_event(dev);
	}

error:
	device_unlock(&dev->dev);

	return rc;
}