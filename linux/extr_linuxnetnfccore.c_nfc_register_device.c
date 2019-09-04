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
struct nfc_dev {int /*<<< orphan*/ * rfkill; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFKILL_TYPE_NFC ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_devlist_generation ; 
 int /*<<< orphan*/  nfc_devlist_mutex ; 
 int nfc_genl_device_added (struct nfc_dev*) ; 
 int nfc_llcp_register_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_rfkill_ops ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/ * rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfc_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ rfkill_register (int /*<<< orphan*/ *) ; 

int nfc_register_device(struct nfc_dev *dev)
{
	int rc;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	mutex_lock(&nfc_devlist_mutex);
	nfc_devlist_generation++;
	rc = device_add(&dev->dev);
	mutex_unlock(&nfc_devlist_mutex);

	if (rc < 0)
		return rc;

	rc = nfc_llcp_register_device(dev);
	if (rc)
		pr_err("Could not register llcp device\n");

	rc = nfc_genl_device_added(dev);
	if (rc)
		pr_debug("The userspace won't be notified that the device %s was added\n",
			 dev_name(&dev->dev));

	dev->rfkill = rfkill_alloc(dev_name(&dev->dev), &dev->dev,
				   RFKILL_TYPE_NFC, &nfc_rfkill_ops, dev);
	if (dev->rfkill) {
		if (rfkill_register(dev->rfkill) < 0) {
			rfkill_destroy(dev->rfkill);
			dev->rfkill = NULL;
		}
	}

	return 0;
}