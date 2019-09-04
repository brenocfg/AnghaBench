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
struct mgmt_pending_cmd {struct mgmt_mode* param; } ;
struct mgmt_mode {int val; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_OP_SET_CONNECTABLE ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

bool mgmt_get_connectable(struct hci_dev *hdev)
{
	struct mgmt_pending_cmd *cmd;

	/* If there's a pending mgmt command the flag will not yet have
	 * it's final value, so check for this first.
	 */
	cmd = pending_find(MGMT_OP_SET_CONNECTABLE, hdev);
	if (cmd) {
		struct mgmt_mode *cp = cmd->param;

		return cp->val;
	}

	return hci_dev_test_flag(hdev, HCI_CONNECTABLE);
}