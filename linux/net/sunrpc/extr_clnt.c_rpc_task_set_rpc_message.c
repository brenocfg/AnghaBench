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
struct TYPE_2__ {int /*<<< orphan*/  rpc_cred; int /*<<< orphan*/  rpc_resp; int /*<<< orphan*/  rpc_argp; int /*<<< orphan*/  rpc_proc; } ;
struct rpc_task {TYPE_1__ tk_msg; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_cred; int /*<<< orphan*/  rpc_resp; int /*<<< orphan*/  rpc_argp; int /*<<< orphan*/  rpc_proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rpc_task_set_rpc_message(struct rpc_task *task, const struct rpc_message *msg)
{
	if (msg != NULL) {
		task->tk_msg.rpc_proc = msg->rpc_proc;
		task->tk_msg.rpc_argp = msg->rpc_argp;
		task->tk_msg.rpc_resp = msg->rpc_resp;
		if (msg->rpc_cred != NULL)
			task->tk_msg.rpc_cred = get_cred(msg->rpc_cred);
	}
}