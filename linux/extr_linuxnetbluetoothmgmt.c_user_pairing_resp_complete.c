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
 int ENOENT ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int user_pairing_resp_complete(struct hci_dev *hdev, bdaddr_t *bdaddr,
				      u8 link_type, u8 addr_type, u8 status,
				      u8 opcode)
{
	struct mgmt_pending_cmd *cmd;

	cmd = pending_find(opcode, hdev);
	if (!cmd)
		return -ENOENT;

	cmd->cmd_complete(cmd, mgmt_status(status));
	mgmt_pending_remove(cmd);

	return 0;
}