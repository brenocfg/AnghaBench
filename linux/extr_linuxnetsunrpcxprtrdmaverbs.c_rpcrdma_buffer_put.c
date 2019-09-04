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
struct rpcrdma_req {int /*<<< orphan*/  rl_list; struct rpcrdma_rep* rl_reply; struct rpcrdma_buffer* rl_buffer; } ;
struct rpcrdma_rep {int /*<<< orphan*/  rr_list; int /*<<< orphan*/  rr_temp; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  rb_recv_bufs; int /*<<< orphan*/  rb_send_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_destroy_rep (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
rpcrdma_buffer_put(struct rpcrdma_req *req)
{
	struct rpcrdma_buffer *buffers = req->rl_buffer;
	struct rpcrdma_rep *rep = req->rl_reply;

	req->rl_reply = NULL;

	spin_lock(&buffers->rb_lock);
	list_add(&req->rl_list, &buffers->rb_send_bufs);
	if (rep) {
		if (!rep->rr_temp) {
			list_add(&rep->rr_list, &buffers->rb_recv_bufs);
			rep = NULL;
		}
	}
	spin_unlock(&buffers->rb_lock);
	if (rep)
		rpcrdma_destroy_rep(rep);
}