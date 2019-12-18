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
struct rpcrdma_req {int /*<<< orphan*/  rl_registered; } ;
struct rpcrdma_mr {int /*<<< orphan*/  mr_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  frwr_mr_recycle (int /*<<< orphan*/ ,struct rpcrdma_mr*) ; 
 struct rpcrdma_mr* rpcrdma_mr_pop (int /*<<< orphan*/ *) ; 

void frwr_recycle(struct rpcrdma_req *req)
{
	struct rpcrdma_mr *mr;

	while ((mr = rpcrdma_mr_pop(&req->rl_registered)))
		frwr_mr_recycle(mr->mr_xprt, mr);
}