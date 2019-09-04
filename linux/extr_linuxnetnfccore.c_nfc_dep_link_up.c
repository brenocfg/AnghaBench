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
typedef  int /*<<< orphan*/  u8 ;
struct nfc_target {int dummy; } ;
struct nfc_dev {int dep_link_up; int /*<<< orphan*/  dev; int /*<<< orphan*/  rf_mode; struct nfc_target* active_target; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dep_link_up ) (struct nfc_dev*,struct nfc_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 size_t NFC_MAX_GT_LEN ; 
 int /*<<< orphan*/  NFC_RF_INITIATOR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_target* nfc_find_target (struct nfc_dev*,int) ; 
 int /*<<< orphan*/ * nfc_llcp_general_bytes (struct nfc_dev*,size_t*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfc_dev*,struct nfc_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int nfc_dep_link_up(struct nfc_dev *dev, int target_index, u8 comm_mode)
{
	int rc = 0;
	u8 *gb;
	size_t gb_len;
	struct nfc_target *target;

	pr_debug("dev_name=%s comm %d\n", dev_name(&dev->dev), comm_mode);

	if (!dev->ops->dep_link_up)
		return -EOPNOTSUPP;

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (dev->dep_link_up == true) {
		rc = -EALREADY;
		goto error;
	}

	gb = nfc_llcp_general_bytes(dev, &gb_len);
	if (gb_len > NFC_MAX_GT_LEN) {
		rc = -EINVAL;
		goto error;
	}

	target = nfc_find_target(dev, target_index);
	if (target == NULL) {
		rc = -ENOTCONN;
		goto error;
	}

	rc = dev->ops->dep_link_up(dev, target, comm_mode, gb, gb_len);
	if (!rc) {
		dev->active_target = target;
		dev->rf_mode = NFC_RF_INITIATOR;
	}

error:
	device_unlock(&dev->dev);
	return rc;
}