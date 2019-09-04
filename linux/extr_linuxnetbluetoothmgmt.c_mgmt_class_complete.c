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
struct mgmt_pending_cmd {int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; int /*<<< orphan*/  sk; } ;
struct hci_dev {int /*<<< orphan*/  dev_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static void mgmt_class_complete(struct hci_dev *hdev, u16 mgmt_op, u8 status)
{
	struct mgmt_pending_cmd *cmd;

	hci_dev_lock(hdev);

	cmd = pending_find(mgmt_op, hdev);
	if (!cmd)
		goto unlock;

	mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode,
			  mgmt_status(status), hdev->dev_class, 3);

	mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
}