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
struct rpcrdma_ia {TYPE_1__* ri_id; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_drain_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_drain_sq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpcrdma_xprt_drain(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;

	/* Flush Receives, then wait for deferred Reply work
	 * to complete.
	 */
	ib_drain_rq(ia->ri_id->qp);

	/* Deferred Reply processing might have scheduled
	 * local invalidations.
	 */
	ib_drain_sq(ia->ri_id->qp);
}