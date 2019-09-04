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
typedef  int /*<<< orphan*/  u8 ;
struct nfc_evt_transaction {int dummy; } ;
struct nfc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int nfc_genl_se_transaction (struct nfc_dev*,int /*<<< orphan*/ ,struct nfc_evt_transaction*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int nfc_se_transaction(struct nfc_dev *dev, u8 se_idx,
		       struct nfc_evt_transaction *evt_transaction)
{
	int rc;

	pr_debug("transaction: %x\n", se_idx);

	device_lock(&dev->dev);

	if (!evt_transaction) {
		rc = -EPROTO;
		goto out;
	}

	rc = nfc_genl_se_transaction(dev, se_idx, evt_transaction);
out:
	device_unlock(&dev->dev);
	return rc;
}