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
struct TYPE_2__ {int rep_max_requests; } ;
struct rpcrdma_buffer {int rb_max_requests; int rb_credits; int /*<<< orphan*/  rb_free_reps; int /*<<< orphan*/  rb_send_bufs; int /*<<< orphan*/  rb_allreqs; int /*<<< orphan*/  rb_refresh_worker; int /*<<< orphan*/  rb_all_mrs; int /*<<< orphan*/  rb_mrs; int /*<<< orphan*/  rb_lock; scalar_t__ rb_bc_srv_max_requests; } ;
struct rpcrdma_xprt {TYPE_1__ rx_ep; struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRDMA_V1_DEF_INLINE_SIZE ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_buffer_destroy (struct rpcrdma_buffer*) ; 
 int /*<<< orphan*/  rpcrdma_mr_refresh_worker ; 
 int /*<<< orphan*/  rpcrdma_mrs_create (struct rpcrdma_xprt*) ; 
 struct rpcrdma_req* rpcrdma_req_create (struct rpcrdma_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpcrdma_sendctxs_create (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int rpcrdma_buffer_create(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	int i, rc;

	buf->rb_max_requests = r_xprt->rx_ep.rep_max_requests;
	buf->rb_bc_srv_max_requests = 0;
	spin_lock_init(&buf->rb_lock);
	INIT_LIST_HEAD(&buf->rb_mrs);
	INIT_LIST_HEAD(&buf->rb_all_mrs);
	INIT_WORK(&buf->rb_refresh_worker, rpcrdma_mr_refresh_worker);

	rpcrdma_mrs_create(r_xprt);

	INIT_LIST_HEAD(&buf->rb_send_bufs);
	INIT_LIST_HEAD(&buf->rb_allreqs);

	rc = -ENOMEM;
	for (i = 0; i < buf->rb_max_requests; i++) {
		struct rpcrdma_req *req;

		req = rpcrdma_req_create(r_xprt, RPCRDMA_V1_DEF_INLINE_SIZE,
					 GFP_KERNEL);
		if (!req)
			goto out;
		list_add(&req->rl_list, &buf->rb_send_bufs);
	}

	buf->rb_credits = 1;
	init_llist_head(&buf->rb_free_reps);

	rc = rpcrdma_sendctxs_create(r_xprt);
	if (rc)
		goto out;

	return 0;
out:
	rpcrdma_buffer_destroy(buf);
	return rc;
}