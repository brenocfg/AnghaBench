#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rpc_cred; } ;
struct rpc_task {int tk_status; TYPE_3__* tk_rqstp; int /*<<< orphan*/  tk_flags; TYPE_2__ tk_msg; } ;
struct rpc_cred {TYPE_1__* cr_ops; } ;
struct TYPE_6__ {struct rpc_cred* rq_cred; } ;
struct TYPE_4__ {int (* crrefresh ) (struct rpc_task*) ;} ;

/* Variables and functions */
 int rpcauth_bindcred (struct rpc_task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rpc_task*) ; 

int
rpcauth_refreshcred(struct rpc_task *task)
{
	struct rpc_cred	*cred;
	int err;

	cred = task->tk_rqstp->rq_cred;
	if (cred == NULL) {
		err = rpcauth_bindcred(task, task->tk_msg.rpc_cred, task->tk_flags);
		if (err < 0)
			goto out;
		cred = task->tk_rqstp->rq_cred;
	}

	err = cred->cr_ops->crrefresh(task);
out:
	if (err < 0)
		task->tk_status = err;
	return err;
}