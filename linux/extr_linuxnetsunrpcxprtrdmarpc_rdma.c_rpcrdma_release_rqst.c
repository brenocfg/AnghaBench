#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  reply_waits_for_send; } ;
struct TYPE_5__ {TYPE_1__* ri_ops; } ;
struct rpcrdma_xprt {TYPE_3__ rx_stats; TYPE_2__ rx_ia; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_flags; int /*<<< orphan*/  rl_registered; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ro_unmap_sync ) (struct rpcrdma_xprt*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRDMA_REQ_F_TX_RESOURCES ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  bit_wait ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_of_line_wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rpcrdma_xprt*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rpcrdma_release_rqst(struct rpcrdma_xprt *r_xprt, struct rpcrdma_req *req)
{
	/* Invalidate and unmap the data payloads before waking
	 * the waiting application. This guarantees the memory
	 * regions are properly fenced from the server before the
	 * application accesses the data. It also ensures proper
	 * send flow control: waking the next RPC waits until this
	 * RPC has relinquished all its Send Queue entries.
	 */
	if (!list_empty(&req->rl_registered))
		r_xprt->rx_ia.ri_ops->ro_unmap_sync(r_xprt,
						    &req->rl_registered);

	/* Ensure that any DMA mapped pages associated with
	 * the Send of the RPC Call have been unmapped before
	 * allowing the RPC to complete. This protects argument
	 * memory not controlled by the RPC client from being
	 * re-used before we're done with it.
	 */
	if (test_bit(RPCRDMA_REQ_F_TX_RESOURCES, &req->rl_flags)) {
		r_xprt->rx_stats.reply_waits_for_send++;
		out_of_line_wait_on_bit(&req->rl_flags,
					RPCRDMA_REQ_F_TX_RESOURCES,
					bit_wait,
					TASK_UNINTERRUPTIBLE);
	}
}