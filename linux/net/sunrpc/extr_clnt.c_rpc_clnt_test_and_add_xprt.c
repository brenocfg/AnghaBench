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
struct sockaddr {int dummy; } ;
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/  addr; } ;
struct rpc_task {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_cb_add_xprt_calldata {int /*<<< orphan*/  xps; int /*<<< orphan*/  xprt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int RPC_TASK_ASYNC ; 
 int RPC_TASK_NULLCREDS ; 
 int RPC_TASK_SOFT ; 
 int RPC_TASK_SOFTCONN ; 
 struct rpc_cb_add_xprt_calldata* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct rpc_task* rpc_call_null_helper (struct rpc_clnt*,struct rpc_xprt*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct rpc_cb_add_xprt_calldata*) ; 
 int /*<<< orphan*/  rpc_cb_add_xprt_call_ops ; 
 int /*<<< orphan*/  rpc_cb_add_xprt_release (struct rpc_cb_add_xprt_calldata*) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 scalar_t__ rpc_xprt_switch_has_addr (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  xprt_get (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_switch_get (struct rpc_xprt_switch*) ; 

int rpc_clnt_test_and_add_xprt(struct rpc_clnt *clnt,
		struct rpc_xprt_switch *xps, struct rpc_xprt *xprt,
		void *dummy)
{
	struct rpc_cb_add_xprt_calldata *data;
	struct rpc_task *task;

	data = kmalloc(sizeof(*data), GFP_NOFS);
	if (!data)
		return -ENOMEM;
	data->xps = xprt_switch_get(xps);
	data->xprt = xprt_get(xprt);
	if (rpc_xprt_switch_has_addr(data->xps, (struct sockaddr *)&xprt->addr)) {
		rpc_cb_add_xprt_release(data);
		goto success;
	}

	task = rpc_call_null_helper(clnt, xprt, NULL,
			RPC_TASK_SOFT|RPC_TASK_SOFTCONN|RPC_TASK_ASYNC|RPC_TASK_NULLCREDS,
			&rpc_cb_add_xprt_call_ops, data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	rpc_put_task(task);
success:
	return 1;
}