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
struct hci_dev {int dummy; } ;
struct cmd_lookup {scalar_t__ sk; int /*<<< orphan*/  member_2; struct hci_dev* member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MGMT_DEV_CLASS_EVENTS ; 
 int /*<<< orphan*/  MGMT_EV_CLASS_OF_DEV_CHANGED ; 
 int /*<<< orphan*/  MGMT_OP_ADD_UUID ; 
 int /*<<< orphan*/  MGMT_OP_REMOVE_UUID ; 
 int /*<<< orphan*/  MGMT_OP_SET_DEV_CLASS ; 
 int /*<<< orphan*/  ext_info_changed (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_pending_foreach (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ,struct cmd_lookup*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_lookup ; 
 int /*<<< orphan*/  sock_put (scalar_t__) ; 

void mgmt_set_class_of_dev_complete(struct hci_dev *hdev, u8 *dev_class,
				    u8 status)
{
	struct cmd_lookup match = { NULL, hdev, mgmt_status(status) };

	mgmt_pending_foreach(MGMT_OP_SET_DEV_CLASS, hdev, sk_lookup, &match);
	mgmt_pending_foreach(MGMT_OP_ADD_UUID, hdev, sk_lookup, &match);
	mgmt_pending_foreach(MGMT_OP_REMOVE_UUID, hdev, sk_lookup, &match);

	if (!status) {
		mgmt_limited_event(MGMT_EV_CLASS_OF_DEV_CHANGED, hdev, dev_class,
				   3, HCI_MGMT_DEV_CLASS_EVENTS, NULL);
		ext_info_changed(hdev, NULL);
	}

	if (match.sk)
		sock_put(match.sk);
}