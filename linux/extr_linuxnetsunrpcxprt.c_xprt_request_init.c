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
struct rpc_xprt {scalar_t__ connect_cookie; } ;
struct rpc_task {int /*<<< orphan*/  tk_pid; TYPE_2__* tk_client; struct rpc_rqst* tk_rqstp; struct rpc_xprt* tk_xprt; } ;
struct TYPE_8__ {scalar_t__ buflen; scalar_t__ len; } ;
struct TYPE_7__ {scalar_t__ buflen; scalar_t__ len; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_xid; int /*<<< orphan*/ * rq_release_snd_buf; TYPE_4__ rq_rcv_buf; TYPE_3__ rq_snd_buf; scalar_t__ rq_bytes_sent; scalar_t__ rq_connect_cookie; int /*<<< orphan*/ * rq_buffer; struct rpc_xprt* rq_xprt; struct rpc_task* rq_task; int /*<<< orphan*/  rq_timeout; int /*<<< orphan*/  rq_list; } ;
struct TYPE_6__ {TYPE_1__* cl_timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  to_initval; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_alloc_xid (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_reset_majortimeo (struct rpc_rqst*) ; 

void xprt_request_init(struct rpc_task *task)
{
	struct rpc_xprt *xprt = task->tk_xprt;
	struct rpc_rqst	*req = task->tk_rqstp;

	INIT_LIST_HEAD(&req->rq_list);
	req->rq_timeout = task->tk_client->cl_timeout->to_initval;
	req->rq_task	= task;
	req->rq_xprt    = xprt;
	req->rq_buffer  = NULL;
	req->rq_xid	= xprt_alloc_xid(xprt);
	req->rq_connect_cookie = xprt->connect_cookie - 1;
	req->rq_bytes_sent = 0;
	req->rq_snd_buf.len = 0;
	req->rq_snd_buf.buflen = 0;
	req->rq_rcv_buf.len = 0;
	req->rq_rcv_buf.buflen = 0;
	req->rq_release_snd_buf = NULL;
	xprt_reset_majortimeo(req);
	dprintk("RPC: %5u reserved req %p xid %08x\n", task->tk_pid,
			req, ntohl(req->rq_xid));
}