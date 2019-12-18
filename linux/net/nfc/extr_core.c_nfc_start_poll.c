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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_dev {int polling; int /*<<< orphan*/  dev; int /*<<< orphan*/  rf_mode; TYPE_1__* ops; int /*<<< orphan*/  dev_up; } ;
struct TYPE_2__ {int (* start_poll ) (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  NFC_RF_NONE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_start_poll(struct nfc_dev *dev, u32 im_protocols, u32 tm_protocols)
{
	int rc;

	pr_debug("dev_name %s initiator protocols 0x%x target protocols 0x%x\n",
		 dev_name(&dev->dev), im_protocols, tm_protocols);

	if (!im_protocols && !tm_protocols)
		return -EINVAL;

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->dev_up) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->polling) {
		rc = -EBUSY;
		goto error;
	}

	rc = dev->ops->start_poll(dev, im_protocols, tm_protocols);
	if (!rc) {
		dev->polling = true;
		dev->rf_mode = NFC_RF_NONE;
	}

error:
	device_unlock(&dev->dev);
	return rc;
}