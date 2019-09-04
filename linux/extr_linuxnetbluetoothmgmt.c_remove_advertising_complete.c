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
typedef  int /*<<< orphan*/  u16 ;
struct mgmt_rp_remove_advertising {int /*<<< orphan*/  instance; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; int /*<<< orphan*/  sk; struct mgmt_cp_remove_advertising* param; } ;
struct mgmt_cp_remove_advertising {int /*<<< orphan*/  instance; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_REMOVE_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_rp_remove_advertising*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static void remove_advertising_complete(struct hci_dev *hdev, u8 status,
					u16 opcode)
{
	struct mgmt_pending_cmd *cmd;
	struct mgmt_cp_remove_advertising *cp;
	struct mgmt_rp_remove_advertising rp;

	BT_DBG("status %d", status);

	hci_dev_lock(hdev);

	/* A failure status here only means that we failed to disable
	 * advertising. Otherwise, the advertising instance has been removed,
	 * so report success.
	 */
	cmd = pending_find(MGMT_OP_REMOVE_ADVERTISING, hdev);
	if (!cmd)
		goto unlock;

	cp = cmd->param;
	rp.instance = cp->instance;

	mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, MGMT_STATUS_SUCCESS,
			  &rp, sizeof(rp));
	mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
}