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
typedef  scalar_t__ u32 ;
struct nfc_dev {int polling; int /*<<< orphan*/  dev; int /*<<< orphan*/  rf_mode; } ;

/* Variables and functions */
 scalar_t__ NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  NFC_RF_TARGET ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_dep_link_is_up (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_genl_tm_activated (struct nfc_dev*,scalar_t__) ; 
 int nfc_set_remote_general_bytes (struct nfc_dev*,int /*<<< orphan*/ *,size_t) ; 

int nfc_tm_activated(struct nfc_dev *dev, u32 protocol, u8 comm_mode,
		     u8 *gb, size_t gb_len)
{
	int rc;

	device_lock(&dev->dev);

	dev->polling = false;

	if (gb != NULL) {
		rc = nfc_set_remote_general_bytes(dev, gb, gb_len);
		if (rc < 0)
			goto out;
	}

	dev->rf_mode = NFC_RF_TARGET;

	if (protocol == NFC_PROTO_NFC_DEP_MASK)
		nfc_dep_link_is_up(dev, 0, comm_mode, NFC_RF_TARGET);

	rc = nfc_genl_tm_activated(dev, protocol);

out:
	device_unlock(&dev->dev);

	return rc;
}