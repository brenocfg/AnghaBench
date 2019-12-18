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
struct rpcrdma_req {int /*<<< orphan*/  rl_rdmabuf; int /*<<< orphan*/  rl_sendbuf; int /*<<< orphan*/  rl_recvbuf; int /*<<< orphan*/  rl_free_mrs; int /*<<< orphan*/  rl_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpcrdma_req*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_mr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_mr_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_free (int /*<<< orphan*/ ) ; 

void rpcrdma_req_destroy(struct rpcrdma_req *req)
{
	list_del(&req->rl_all);

	while (!list_empty(&req->rl_free_mrs))
		rpcrdma_mr_free(rpcrdma_mr_pop(&req->rl_free_mrs));

	rpcrdma_regbuf_free(req->rl_recvbuf);
	rpcrdma_regbuf_free(req->rl_sendbuf);
	rpcrdma_regbuf_free(req->rl_rdmabuf);
	kfree(req);
}