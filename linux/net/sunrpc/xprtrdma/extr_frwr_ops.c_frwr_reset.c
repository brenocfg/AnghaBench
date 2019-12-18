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
struct rpcrdma_mr {int dummy; } ;

/* Variables and functions */
 struct rpcrdma_mr* rpcrdma_mr_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_mr_put (struct rpcrdma_mr*) ; 

void frwr_reset(struct rpcrdma_req *req)
{
	struct rpcrdma_mr *mr;

	while ((mr = rpcrdma_mr_pop(&req->rl_registered)))
		rpcrdma_mr_put(mr);
}