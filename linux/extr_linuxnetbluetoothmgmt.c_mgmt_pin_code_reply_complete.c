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
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;} ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_OP_PIN_CODE_REPLY ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

void mgmt_pin_code_reply_complete(struct hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 status)
{
	struct mgmt_pending_cmd *cmd;

	cmd = pending_find(MGMT_OP_PIN_CODE_REPLY, hdev);
	if (!cmd)
		return;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_remove(cmd);
}