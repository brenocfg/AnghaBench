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
struct nfc_dev {int fw_download_in_progress; int /*<<< orphan*/  dev; TYPE_1__* ops; scalar_t__ dev_up; } ;
struct TYPE_2__ {int (* fw_download ) (struct nfc_dev*,char const*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*) ; 
 int stub1 (struct nfc_dev*,char const*) ; 

int nfc_fw_download(struct nfc_dev *dev, const char *firmware_name)
{
	int rc = 0;

	pr_debug("%s do firmware %s\n", dev_name(&dev->dev), firmware_name);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->dev_up) {
		rc = -EBUSY;
		goto error;
	}

	if (!dev->ops->fw_download) {
		rc = -EOPNOTSUPP;
		goto error;
	}

	dev->fw_download_in_progress = true;
	rc = dev->ops->fw_download(dev, firmware_name);
	if (rc)
		dev->fw_download_in_progress = false;

error:
	device_unlock(&dev->dev);
	return rc;
}