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
struct sockaddr {int dummy; } ;
struct rpc_xprt_switch {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/ * address_strings; int /*<<< orphan*/  addr; } ;
struct rpc_task {int tk_status; } ;
struct rpc_cred {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_add_xprt_test {int /*<<< orphan*/  data; int /*<<< orphan*/  (* add_xprt_test ) (struct rpc_clnt*,struct rpc_xprt*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct rpc_cred* (* lookup_cred ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EADDRINUSE ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 size_t RPC_DISPLAY_ADDR ; 
 int RPC_TASK_SOFT ; 
 int RPC_TASK_SOFTCONN ; 
 TYPE_1__ authnull_ops ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_task* rpc_call_null_helper (struct rpc_clnt*,struct rpc_xprt*,struct rpc_cred*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 scalar_t__ rpc_xprt_switch_has_addr (struct rpc_xprt_switch*,struct sockaddr*) ; 
 struct rpc_cred* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rpc_clnt*,struct rpc_xprt*,int /*<<< orphan*/ ) ; 
 struct rpc_xprt* xprt_get (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_switch_get (struct rpc_xprt_switch*) ; 
 int /*<<< orphan*/  xprt_switch_put (struct rpc_xprt_switch*) ; 

int rpc_clnt_setup_test_and_add_xprt(struct rpc_clnt *clnt,
				     struct rpc_xprt_switch *xps,
				     struct rpc_xprt *xprt,
				     void *data)
{
	struct rpc_cred *cred;
	struct rpc_task *task;
	struct rpc_add_xprt_test *xtest = (struct rpc_add_xprt_test *)data;
	int status = -EADDRINUSE;

	xprt = xprt_get(xprt);
	xprt_switch_get(xps);

	if (rpc_xprt_switch_has_addr(xps, (struct sockaddr *)&xprt->addr))
		goto out_err;

	/* Test the connection */
	cred = authnull_ops.lookup_cred(NULL, NULL, 0);
	task = rpc_call_null_helper(clnt, xprt, cred,
				    RPC_TASK_SOFT | RPC_TASK_SOFTCONN,
				    NULL, NULL);
	put_rpccred(cred);
	if (IS_ERR(task)) {
		status = PTR_ERR(task);
		goto out_err;
	}
	status = task->tk_status;
	rpc_put_task(task);

	if (status < 0)
		goto out_err;

	/* rpc_xprt_switch and rpc_xprt are deferrenced by add_xprt_test() */
	xtest->add_xprt_test(clnt, xprt, xtest->data);

	/* so that rpc_clnt_add_xprt does not call rpc_xprt_switch_add_xprt */
	return 1;
out_err:
	xprt_put(xprt);
	xprt_switch_put(xps);
	pr_info("RPC:   rpc_clnt_test_xprt failed: %d addr %s not added\n",
		status, xprt->address_strings[RPC_DISPLAY_ADDR]);
	return status;
}