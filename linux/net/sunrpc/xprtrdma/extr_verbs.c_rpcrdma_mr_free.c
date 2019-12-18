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
struct rpcrdma_buffer {int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  rb_mrs; } ;
struct rpcrdma_xprt {struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_mr {int /*<<< orphan*/ * mr_req; struct rpcrdma_xprt* mr_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcrdma_mr_push (struct rpcrdma_mr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpcrdma_mr_free(struct rpcrdma_mr *mr)
{
	struct rpcrdma_xprt *r_xprt = mr->mr_xprt;
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;

	mr->mr_req = NULL;
	spin_lock(&buf->rb_lock);
	rpcrdma_mr_push(mr, &buf->rb_mrs);
	spin_unlock(&buf->rb_lock);
}