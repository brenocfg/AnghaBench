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
struct rpcrdma_buffer {int /*<<< orphan*/  rb_reqslock; } ;
struct rpcrdma_xprt {struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_all; } ;
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct rpcrdma_req* rpcr_to_rdmar (struct rpc_rqst*) ; 
 int /*<<< orphan*/  rpcrdma_destroy_req (struct rpcrdma_req*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpcrdma_bc_free_rqst(struct rpcrdma_xprt *r_xprt,
				 struct rpc_rqst *rqst)
{
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	struct rpcrdma_req *req = rpcr_to_rdmar(rqst);

	spin_lock(&buf->rb_reqslock);
	list_del(&req->rl_all);
	spin_unlock(&buf->rb_reqslock);

	rpcrdma_destroy_req(req);
}