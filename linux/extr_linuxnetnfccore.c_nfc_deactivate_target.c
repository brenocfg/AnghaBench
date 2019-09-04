#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nfc_dev {int /*<<< orphan*/  dev; TYPE_2__* active_target; TYPE_1__* ops; int /*<<< orphan*/  check_pres_timer; } ;
struct TYPE_4__ {scalar_t__ idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* deactivate_target ) (struct nfc_dev*,TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ check_presence; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nfc_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 

int nfc_deactivate_target(struct nfc_dev *dev, u32 target_idx, u8 mode)
{
	int rc = 0;

	pr_debug("dev_name=%s target_idx=%u\n",
		 dev_name(&dev->dev), target_idx);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->active_target == NULL) {
		rc = -ENOTCONN;
		goto error;
	}

	if (dev->active_target->idx != target_idx) {
		rc = -ENOTCONN;
		goto error;
	}

	if (dev->ops->check_presence)
		del_timer_sync(&dev->check_pres_timer);

	dev->ops->deactivate_target(dev, dev->active_target, mode);
	dev->active_target = NULL;

error:
	device_unlock(&dev->dev);
	return rc;
}