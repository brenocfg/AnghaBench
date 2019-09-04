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
struct rpc_message {int /*<<< orphan*/  rpc_cred; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lookup_cred ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int RPC_TASK_SOFT ; 
 int RPC_TASK_SOFTCONN ; 
 TYPE_1__ authnull_ops ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int rpc_call_sync (struct rpc_clnt*,struct rpc_message*,int) ; 
 int /*<<< orphan*/  rpcproc_null ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_ping(struct rpc_clnt *clnt)
{
	struct rpc_message msg = {
		.rpc_proc = &rpcproc_null,
	};
	int err;
	msg.rpc_cred = authnull_ops.lookup_cred(NULL, NULL, 0);
	err = rpc_call_sync(clnt, &msg, RPC_TASK_SOFT | RPC_TASK_SOFTCONN);
	put_rpccred(msg.rpc_cred);
	return err;
}