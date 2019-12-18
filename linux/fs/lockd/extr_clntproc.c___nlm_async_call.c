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
typedef  size_t u32 ;
struct rpc_task_setup {struct rpc_clnt* rpc_client; int /*<<< orphan*/  flags; struct nlm_rqst* callback_data; struct rpc_call_ops const* callback_ops; struct rpc_message* rpc_message; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int /*<<< orphan*/ * cl_procinfo; } ;
struct rpc_call_ops {int /*<<< orphan*/  (* rpc_release ) (struct nlm_rqst*) ;} ;
struct nlm_rqst {struct nlm_host* a_host; } ;
struct nlm_host {int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOLCK ; 
 struct rpc_task* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 
 struct rpc_clnt* nlm_bind_host (struct nlm_host*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int /*<<< orphan*/  stub1 (struct nlm_rqst*) ; 

__attribute__((used)) static struct rpc_task *__nlm_async_call(struct nlm_rqst *req, u32 proc, struct rpc_message *msg, const struct rpc_call_ops *tk_ops)
{
	struct nlm_host	*host = req->a_host;
	struct rpc_clnt	*clnt;
	struct rpc_task_setup task_setup_data = {
		.rpc_message = msg,
		.callback_ops = tk_ops,
		.callback_data = req,
		.flags = RPC_TASK_ASYNC,
	};

	dprintk("lockd: call procedure %d on %s (async)\n",
			(int)proc, host->h_name);

	/* If we have no RPC client yet, create one. */
	clnt = nlm_bind_host(host);
	if (clnt == NULL)
		goto out_err;
	msg->rpc_proc = &clnt->cl_procinfo[proc];
	task_setup_data.rpc_client = clnt;

        /* bootstrap and kick off the async RPC call */
	return rpc_run_task(&task_setup_data);
out_err:
	tk_ops->rpc_release(req);
	return ERR_PTR(-ENOLCK);
}