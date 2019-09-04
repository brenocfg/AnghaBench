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
struct nfc_llcp_local {int /*<<< orphan*/  remote_lto; int /*<<< orphan*/  link_timer; int /*<<< orphan*/  tx_work; scalar_t__ rf_mode; scalar_t__ comm_mode; int /*<<< orphan*/  target_idx; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFC_RF_INITIATOR ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void nfc_llcp_mac_is_up(struct nfc_dev *dev, u32 target_idx,
			u8 comm_mode, u8 rf_mode)
{
	struct nfc_llcp_local *local;

	pr_debug("rf mode %d\n", rf_mode);

	local = nfc_llcp_find_local(dev);
	if (local == NULL)
		return;

	local->target_idx = target_idx;
	local->comm_mode = comm_mode;
	local->rf_mode = rf_mode;

	if (rf_mode == NFC_RF_INITIATOR) {
		pr_debug("Queueing Tx work\n");

		schedule_work(&local->tx_work);
	} else {
		mod_timer(&local->link_timer,
			  jiffies + msecs_to_jiffies(local->remote_lto));
	}
}