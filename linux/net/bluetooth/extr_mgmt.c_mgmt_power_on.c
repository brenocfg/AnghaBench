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
struct hci_dev {int dummy; } ;
struct cmd_lookup {scalar_t__ sk; struct hci_dev* member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int /*<<< orphan*/  MGMT_OP_SET_POWERED ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_pending_foreach (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ,struct cmd_lookup*) ; 
 int /*<<< orphan*/  new_settings (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  restart_le_actions (struct hci_dev*) ; 
 int /*<<< orphan*/  settings_rsp ; 
 int /*<<< orphan*/  sock_put (scalar_t__) ; 

void mgmt_power_on(struct hci_dev *hdev, int err)
{
	struct cmd_lookup match = { NULL, hdev };

	BT_DBG("err %d", err);

	hci_dev_lock(hdev);

	if (!err) {
		restart_le_actions(hdev);
		hci_update_background_scan(hdev);
	}

	mgmt_pending_foreach(MGMT_OP_SET_POWERED, hdev, settings_rsp, &match);

	new_settings(hdev, match.sk);

	if (match.sk)
		sock_put(match.sk);

	hci_dev_unlock(hdev);
}