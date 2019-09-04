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
typedef  int /*<<< orphan*/  zero_cod ;
struct cmd_lookup {scalar_t__ sk; struct hci_dev* member_1; int /*<<< orphan*/ * member_0; } ;
typedef  struct cmd_lookup u8 ;
struct hci_dev {int /*<<< orphan*/  dev_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_MGMT_DEV_CLASS_EVENTS ; 
 int /*<<< orphan*/  HCI_UNREGISTER ; 
 int /*<<< orphan*/  MGMT_EV_CLASS_OF_DEV_CHANGED ; 
 int /*<<< orphan*/  MGMT_OP_SET_POWERED ; 
 struct cmd_lookup MGMT_STATUS_INVALID_INDEX ; 
 struct cmd_lookup MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  cmd_complete_rsp ; 
 int /*<<< orphan*/  ext_info_changed (struct hci_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,struct cmd_lookup*,int) ; 
 int /*<<< orphan*/  mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,struct cmd_lookup*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_pending_foreach (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ,struct cmd_lookup*) ; 
 int /*<<< orphan*/  new_settings (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  settings_rsp ; 
 int /*<<< orphan*/  sock_put (scalar_t__) ; 

void __mgmt_power_off(struct hci_dev *hdev)
{
	struct cmd_lookup match = { NULL, hdev };
	u8 status, zero_cod[] = { 0, 0, 0 };

	mgmt_pending_foreach(MGMT_OP_SET_POWERED, hdev, settings_rsp, &match);

	/* If the power off is because of hdev unregistration let
	 * use the appropriate INVALID_INDEX status. Otherwise use
	 * NOT_POWERED. We cover both scenarios here since later in
	 * mgmt_index_removed() any hci_conn callbacks will have already
	 * been triggered, potentially causing misleading DISCONNECTED
	 * status responses.
	 */
	if (hci_dev_test_flag(hdev, HCI_UNREGISTER))
		status = MGMT_STATUS_INVALID_INDEX;
	else
		status = MGMT_STATUS_NOT_POWERED;

	mgmt_pending_foreach(0, hdev, cmd_complete_rsp, &status);

	if (memcmp(hdev->dev_class, zero_cod, sizeof(zero_cod)) != 0) {
		mgmt_limited_event(MGMT_EV_CLASS_OF_DEV_CHANGED, hdev,
				   zero_cod, sizeof(zero_cod),
				   HCI_MGMT_DEV_CLASS_EVENTS, NULL);
		ext_info_changed(hdev, NULL);
	}

	new_settings(hdev, match.sk);

	if (match.sk)
		sock_put(match.sk);
}