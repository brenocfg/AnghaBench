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
struct rpcrdma_buffer {int /*<<< orphan*/  rb_recovery_worker; int /*<<< orphan*/  rb_recovery_lock; int /*<<< orphan*/  rb_stale_mrs; } ;
struct rpcrdma_xprt {struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_mr {struct rpcrdma_xprt* mr_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcrdma_mr_push (struct rpcrdma_mr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
rpcrdma_mr_defer_recovery(struct rpcrdma_mr *mr)
{
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;

	spin_lock(&buf->rb_recovery_lock);
	rpcrdma_mr_push(mr, &buf->rb_stale_mrs);
	spin_unlock(&buf->rb_recovery_lock);

	schedule_delayed_work(&buf->rb_recovery_worker, 0);
}