#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpcrdma_req {TYPE_2__* rl_sendctx; } ;
struct rpcrdma_ia {TYPE_1__* ri_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_wr; } ;
struct TYPE_3__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int ib_post_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fmr_op_send(struct rpcrdma_ia *ia, struct rpcrdma_req *req)
{
	return ib_post_send(ia->ri_id->qp, &req->rl_sendctx->sc_wr, NULL);
}