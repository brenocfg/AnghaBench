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
struct rpcrdma_req {int /*<<< orphan*/  rl_rdmabuf; int /*<<< orphan*/  rl_sendbuf; int /*<<< orphan*/  rl_recvbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpcrdma_req*) ; 
 int /*<<< orphan*/  rpcrdma_free_regbuf (int /*<<< orphan*/ ) ; 

void
rpcrdma_destroy_req(struct rpcrdma_req *req)
{
	rpcrdma_free_regbuf(req->rl_recvbuf);
	rpcrdma_free_regbuf(req->rl_sendbuf);
	rpcrdma_free_regbuf(req->rl_rdmabuf);
	kfree(req);
}