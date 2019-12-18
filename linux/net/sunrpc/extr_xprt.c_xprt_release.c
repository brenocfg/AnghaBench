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
struct rpc_xprt {TYPE_1__* ops; int /*<<< orphan*/  transport_lock; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; struct rpc_rqst* tk_rqstp; struct rpc_xprt* tk_xprt; scalar_t__ tk_client; } ;
struct rpc_rqst {int /*<<< orphan*/  (* rq_release_snd_buf ) (struct rpc_rqst*) ;int /*<<< orphan*/ * rq_cred; int /*<<< orphan*/  rq_snd_buf; int /*<<< orphan*/  rq_rcv_buf; scalar_t__ rq_buffer; struct rpc_xprt* rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_slot ) (struct rpc_xprt*,struct rpc_rqst*) ;int /*<<< orphan*/  (* buf_free ) (struct rpc_task*) ;int /*<<< orphan*/  (* release_request ) (struct rpc_task*) ;int /*<<< orphan*/  (* release_xprt ) (struct rpc_xprt*,struct rpc_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bc_prealloc (struct rpc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_rqst*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_task*) ; 
 int /*<<< orphan*/  stub3 (struct rpc_task*) ; 
 int /*<<< orphan*/  stub4 (struct rpc_rqst*) ; 
 int /*<<< orphan*/  stub5 (struct rpc_xprt*,struct rpc_rqst*) ; 
 int /*<<< orphan*/  xdr_free_bvec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_free_bc_request (struct rpc_rqst*) ; 
 int /*<<< orphan*/  xprt_inject_disconnect (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_release_write (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_request_dequeue_xprt (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_schedule_autodisconnect (struct rpc_xprt*) ; 

void xprt_release(struct rpc_task *task)
{
	struct rpc_xprt	*xprt;
	struct rpc_rqst	*req = task->tk_rqstp;

	if (req == NULL) {
		if (task->tk_client) {
			xprt = task->tk_xprt;
			xprt_release_write(xprt, task);
		}
		return;
	}

	xprt = req->rq_xprt;
	xprt_request_dequeue_xprt(task);
	spin_lock(&xprt->transport_lock);
	xprt->ops->release_xprt(xprt, task);
	if (xprt->ops->release_request)
		xprt->ops->release_request(task);
	xprt_schedule_autodisconnect(xprt);
	spin_unlock(&xprt->transport_lock);
	if (req->rq_buffer)
		xprt->ops->buf_free(task);
	xprt_inject_disconnect(xprt);
	xdr_free_bvec(&req->rq_rcv_buf);
	xdr_free_bvec(&req->rq_snd_buf);
	if (req->rq_cred != NULL)
		put_rpccred(req->rq_cred);
	task->tk_rqstp = NULL;
	if (req->rq_release_snd_buf)
		req->rq_release_snd_buf(req);

	dprintk("RPC: %5u release request %p\n", task->tk_pid, req);
	if (likely(!bc_prealloc(req)))
		xprt->ops->free_slot(xprt, req);
	else
		xprt_free_bc_request(req);
}