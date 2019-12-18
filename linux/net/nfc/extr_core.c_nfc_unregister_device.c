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
struct nfc_dev {int shutting_down; int /*<<< orphan*/  dev; int /*<<< orphan*/  check_pres_work; int /*<<< orphan*/  check_pres_timer; TYPE_1__* ops; scalar_t__ rfkill; } ;
struct TYPE_2__ {scalar_t__ check_presence; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_devlist_generation ; 
 int /*<<< orphan*/  nfc_devlist_mutex ; 
 int nfc_genl_device_removed (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_llcp_unregister_device (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 

void nfc_unregister_device(struct nfc_dev *dev)
{
	int rc;

	pr_debug("dev_name=%s\n", dev_name(&dev->dev));

	if (dev->rfkill) {
		rfkill_unregister(dev->rfkill);
		rfkill_destroy(dev->rfkill);
	}

	if (dev->ops->check_presence) {
		device_lock(&dev->dev);
		dev->shutting_down = true;
		device_unlock(&dev->dev);
		del_timer_sync(&dev->check_pres_timer);
		cancel_work_sync(&dev->check_pres_work);
	}

	rc = nfc_genl_device_removed(dev);
	if (rc)
		pr_debug("The userspace won't be notified that the device %s "
			 "was removed\n", dev_name(&dev->dev));

	nfc_llcp_unregister_device(dev);

	mutex_lock(&nfc_devlist_mutex);
	nfc_devlist_generation++;
	device_del(&dev->dev);
	mutex_unlock(&nfc_devlist_mutex);
}