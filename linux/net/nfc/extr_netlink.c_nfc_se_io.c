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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_se {scalar_t__ state; } ;
struct nfc_dev {int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  dev_up; } ;
typedef  int /*<<< orphan*/  se_io_cb_t ;
struct TYPE_2__ {int (* se_io ) (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ NFC_SE_ENABLED ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 struct nfc_se* nfc_find_se (struct nfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int nfc_se_io(struct nfc_dev *dev, u32 se_idx,
		     u8 *apdu, size_t apdu_length,
		     se_io_cb_t cb, void *cb_context)
{
	struct nfc_se *se;
	int rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_lock(&dev->dev);

	if (!device_is_registered(&dev->dev)) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->dev_up) {
		rc = -ENODEV;
		goto error;
	}

	if (!dev->ops->se_io) {
		rc = -EOPNOTSUPP;
		goto error;
	}

	se = nfc_find_se(dev, se_idx);
	if (!se) {
		rc = -EINVAL;
		goto error;
	}

	if (se->state != NFC_SE_ENABLED) {
		rc = -ENODEV;
		goto error;
	}

	rc = dev->ops->se_io(dev, se_idx, apdu,
			apdu_length, cb, cb_context);

error:
	device_unlock(&dev->dev);
	return rc;
}