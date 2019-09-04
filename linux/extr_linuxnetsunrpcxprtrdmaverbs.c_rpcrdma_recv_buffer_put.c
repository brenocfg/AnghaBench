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
struct rpcrdma_rep {int /*<<< orphan*/  rr_list; int /*<<< orphan*/  rr_temp; TYPE_1__* rr_rxprt; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  rb_recv_bufs; } ;
struct TYPE_2__ {struct rpcrdma_buffer rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_destroy_rep (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
rpcrdma_recv_buffer_put(struct rpcrdma_rep *rep)
{
	struct rpcrdma_buffer *buffers = &rep->rr_rxprt->rx_buf;

	if (!rep->rr_temp) {
		spin_lock(&buffers->rb_lock);
		list_add(&rep->rr_list, &buffers->rb_recv_bufs);
		spin_unlock(&buffers->rb_lock);
	} else {
		rpcrdma_destroy_rep(rep);
	}
}