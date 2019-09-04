#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_pin_code_neg_reply {TYPE_1__ addr; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_OP_PIN_CODE_NEG_REPLY ; 
 int /*<<< orphan*/  MGMT_OP_PIN_CODE_NEG_REPLY ; 
 int /*<<< orphan*/  addr_cmd_complete ; 
 int hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_cp_pin_code_neg_reply*,int) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 

__attribute__((used)) static int send_pin_code_neg_reply(struct sock *sk, struct hci_dev *hdev,
				   struct mgmt_cp_pin_code_neg_reply *cp)
{
	struct mgmt_pending_cmd *cmd;
	int err;

	cmd = mgmt_pending_add(sk, MGMT_OP_PIN_CODE_NEG_REPLY, hdev, cp,
			       sizeof(*cp));
	if (!cmd)
		return -ENOMEM;

	cmd->cmd_complete = addr_cmd_complete;

	err = hci_send_cmd(hdev, HCI_OP_PIN_CODE_NEG_REPLY,
			   sizeof(cp->addr.bdaddr), &cp->addr.bdaddr);
	if (err < 0)
		mgmt_pending_remove(cmd);

	return err;
}