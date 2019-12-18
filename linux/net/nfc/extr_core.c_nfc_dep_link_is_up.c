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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfc_target {int dummy; } ;
struct nfc_dev {int dep_link_up; int polling; scalar_t__ rf_mode; struct nfc_target* active_target; } ;

/* Variables and functions */
 int ENOTCONN ; 
 scalar_t__ NFC_RF_INITIATOR ; 
 struct nfc_target* nfc_find_target (struct nfc_dev*,int /*<<< orphan*/ ) ; 
 int nfc_genl_dep_link_up_event (struct nfc_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfc_llcp_mac_is_up (struct nfc_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int nfc_dep_link_is_up(struct nfc_dev *dev, u32 target_idx,
		       u8 comm_mode, u8 rf_mode)
{
	dev->dep_link_up = true;

	if (!dev->active_target && rf_mode == NFC_RF_INITIATOR) {
		struct nfc_target *target;

		target = nfc_find_target(dev, target_idx);
		if (target == NULL)
			return -ENOTCONN;

		dev->active_target = target;
	}

	dev->polling = false;
	dev->rf_mode = rf_mode;

	nfc_llcp_mac_is_up(dev, target_idx, comm_mode, rf_mode);

	return nfc_genl_dep_link_up_event(dev, target_idx, comm_mode, rf_mode);
}