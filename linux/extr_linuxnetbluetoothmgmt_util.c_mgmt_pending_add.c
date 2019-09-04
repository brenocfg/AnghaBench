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
typedef  void* u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  list; struct sock* sk; void* param_len; int /*<<< orphan*/  param; int /*<<< orphan*/  index; void* opcode; } ;
struct hci_dev {int /*<<< orphan*/  mgmt_pending; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  kmemdup (void*,void*,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

struct mgmt_pending_cmd *mgmt_pending_add(struct sock *sk, u16 opcode,
					  struct hci_dev *hdev,
					  void *data, u16 len)
{
	struct mgmt_pending_cmd *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return NULL;

	cmd->opcode = opcode;
	cmd->index = hdev->id;

	cmd->param = kmemdup(data, len, GFP_KERNEL);
	if (!cmd->param) {
		kfree(cmd);
		return NULL;
	}

	cmd->param_len = len;

	cmd->sk = sk;
	sock_hold(sk);

	list_add(&cmd->list, &hdev->mgmt_pending);

	return cmd;
}