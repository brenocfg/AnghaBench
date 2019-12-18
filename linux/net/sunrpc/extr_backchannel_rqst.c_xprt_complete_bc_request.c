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
typedef  int /*<<< orphan*/  uint32_t ;
struct svc_serv {int /*<<< orphan*/  sv_cb_lock; int /*<<< orphan*/  sv_cb_waitq; int /*<<< orphan*/  sv_cb_list; } ;
struct rpc_xprt {int /*<<< orphan*/  bc_pa_lock; int /*<<< orphan*/  bc_alloc_count; struct svc_serv* bc_serv; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_bc_list; int /*<<< orphan*/  rq_bc_pa_state; TYPE_1__ rq_private_buf; int /*<<< orphan*/  rq_bc_pa_list; struct rpc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_BC_PA_IN_USE ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_get (struct rpc_xprt*) ; 

void xprt_complete_bc_request(struct rpc_rqst *req, uint32_t copied)
{
	struct rpc_xprt *xprt = req->rq_xprt;
	struct svc_serv *bc_serv = xprt->bc_serv;

	spin_lock(&xprt->bc_pa_lock);
	list_del(&req->rq_bc_pa_list);
	xprt->bc_alloc_count--;
	spin_unlock(&xprt->bc_pa_lock);

	req->rq_private_buf.len = copied;
	set_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state);

	dprintk("RPC:       add callback request to list\n");
	xprt_get(xprt);
	spin_lock(&bc_serv->sv_cb_lock);
	list_add(&req->rq_bc_list, &bc_serv->sv_cb_list);
	wake_up(&bc_serv->sv_cb_waitq);
	spin_unlock(&bc_serv->sv_cb_lock);
}