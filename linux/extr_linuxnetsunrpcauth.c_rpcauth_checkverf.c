#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int /*<<< orphan*/  tk_pid; TYPE_1__* tk_rqstp; } ;
struct rpc_cred {TYPE_4__* cr_ops; TYPE_3__* cr_auth; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int /*<<< orphan*/ * (* crvalidate ) (struct rpc_task*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_2__* au_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  au_name; } ;
struct TYPE_5__ {struct rpc_cred* rq_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_cred*) ; 
 int /*<<< orphan*/ * stub1 (struct rpc_task*,int /*<<< orphan*/ *) ; 

__be32 *
rpcauth_checkverf(struct rpc_task *task, __be32 *p)
{
	struct rpc_cred	*cred = task->tk_rqstp->rq_cred;

	dprintk("RPC: %5u validating %s cred %p\n",
		task->tk_pid, cred->cr_auth->au_ops->au_name, cred);

	return cred->cr_ops->crvalidate(task, p);
}