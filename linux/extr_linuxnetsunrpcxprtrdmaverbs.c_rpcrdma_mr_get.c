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
struct TYPE_2__ {int /*<<< orphan*/  rep_connected; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_refresh_worker; int /*<<< orphan*/  rb_mrlock; int /*<<< orphan*/  rb_mrs; } ;
struct rpcrdma_xprt {TYPE_1__ rx_ep; struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct rpcrdma_mr* rpcrdma_mr_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xprtrdma_nomrs (struct rpcrdma_xprt*) ; 

struct rpcrdma_mr *
rpcrdma_mr_get(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	struct rpcrdma_mr *mr = NULL;

	spin_lock(&buf->rb_mrlock);
	if (!list_empty(&buf->rb_mrs))
		mr = rpcrdma_mr_pop(&buf->rb_mrs);
	spin_unlock(&buf->rb_mrlock);

	if (!mr)
		goto out_nomrs;
	return mr;

out_nomrs:
	trace_xprtrdma_nomrs(r_xprt);
	if (r_xprt->rx_ep.rep_connected != -ENODEV)
		schedule_delayed_work(&buf->rb_refresh_worker, 0);

	/* Allow the reply handler and refresh worker to run */
	cond_resched();

	return NULL;
}