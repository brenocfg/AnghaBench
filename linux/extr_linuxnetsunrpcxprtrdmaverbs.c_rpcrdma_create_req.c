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
struct rpcrdma_buffer {int /*<<< orphan*/  rb_reqslock; int /*<<< orphan*/  rb_allreqs; } ;
struct rpcrdma_xprt {struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_req {int /*<<< orphan*/  rl_all; int /*<<< orphan*/  rl_registered; struct rpcrdma_buffer* rl_buffer; int /*<<< orphan*/  rl_hdrbuf; struct rpcrdma_regbuf* rl_rdmabuf; } ;
struct rpcrdma_regbuf {int /*<<< orphan*/  rg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct rpcrdma_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  RPCRDMA_HDRBUF_SIZE ; 
 int /*<<< orphan*/  kfree (struct rpcrdma_req*) ; 
 struct rpcrdma_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmab_length (struct rpcrdma_regbuf*) ; 
 struct rpcrdma_regbuf* rpcrdma_alloc_regbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rpcrdma_req *
rpcrdma_create_req(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_buffer *buffer = &r_xprt->rx_buf;
	struct rpcrdma_regbuf *rb;
	struct rpcrdma_req *req;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (req == NULL)
		return ERR_PTR(-ENOMEM);

	rb = rpcrdma_alloc_regbuf(RPCRDMA_HDRBUF_SIZE,
				  DMA_TO_DEVICE, GFP_KERNEL);
	if (IS_ERR(rb)) {
		kfree(req);
		return ERR_PTR(-ENOMEM);
	}
	req->rl_rdmabuf = rb;
	xdr_buf_init(&req->rl_hdrbuf, rb->rg_base, rdmab_length(rb));
	req->rl_buffer = buffer;
	INIT_LIST_HEAD(&req->rl_registered);

	spin_lock(&buffer->rb_reqslock);
	list_add(&req->rl_all, &buffer->rb_allreqs);
	spin_unlock(&buffer->rb_reqslock);
	return req;
}