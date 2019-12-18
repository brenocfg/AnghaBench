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
struct TYPE_2__ {int ri_max_segs; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  rb_allreqs; } ;
struct rpcrdma_xprt {TYPE_1__ rx_ia; struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_req {struct rpcrdma_req* rl_rdmabuf; struct rpcrdma_req* rl_sendbuf; int /*<<< orphan*/  rl_all; int /*<<< orphan*/  rl_registered; int /*<<< orphan*/  rl_free_mrs; void* rl_recvbuf; int /*<<< orphan*/  rl_hdrbuf; } ;
struct rpcrdma_regbuf {struct rpcrdma_regbuf* rl_rdmabuf; struct rpcrdma_regbuf* rl_sendbuf; int /*<<< orphan*/  rl_all; int /*<<< orphan*/  rl_registered; int /*<<< orphan*/  rl_free_mrs; void* rl_recvbuf; int /*<<< orphan*/  rl_hdrbuf; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t __roundup_pow_of_two (size_t) ; 
 int /*<<< orphan*/  kfree (struct rpcrdma_req*) ; 
 struct rpcrdma_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmab_data (struct rpcrdma_req*) ; 
 int /*<<< orphan*/  rdmab_length (struct rpcrdma_req*) ; 
 int rpcrdma_fixed_maxsz ; 
 int rpcrdma_readchunk_maxsz ; 
 void* rpcrdma_regbuf_alloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rpcrdma_req *rpcrdma_req_create(struct rpcrdma_xprt *r_xprt, size_t size,
				       gfp_t flags)
{
	struct rpcrdma_buffer *buffer = &r_xprt->rx_buf;
	struct rpcrdma_regbuf *rb;
	struct rpcrdma_req *req;
	size_t maxhdrsize;

	req = kzalloc(sizeof(*req), flags);
	if (req == NULL)
		goto out1;

	/* Compute maximum header buffer size in bytes */
	maxhdrsize = rpcrdma_fixed_maxsz + 3 +
		     r_xprt->rx_ia.ri_max_segs * rpcrdma_readchunk_maxsz;
	maxhdrsize *= sizeof(__be32);
	rb = rpcrdma_regbuf_alloc(__roundup_pow_of_two(maxhdrsize),
				  DMA_TO_DEVICE, flags);
	if (!rb)
		goto out2;
	req->rl_rdmabuf = rb;
	xdr_buf_init(&req->rl_hdrbuf, rdmab_data(rb), rdmab_length(rb));

	req->rl_sendbuf = rpcrdma_regbuf_alloc(size, DMA_TO_DEVICE, flags);
	if (!req->rl_sendbuf)
		goto out3;

	req->rl_recvbuf = rpcrdma_regbuf_alloc(size, DMA_NONE, flags);
	if (!req->rl_recvbuf)
		goto out4;

	INIT_LIST_HEAD(&req->rl_free_mrs);
	INIT_LIST_HEAD(&req->rl_registered);
	spin_lock(&buffer->rb_lock);
	list_add(&req->rl_all, &buffer->rb_allreqs);
	spin_unlock(&buffer->rb_lock);
	return req;

out4:
	kfree(req->rl_sendbuf);
out3:
	kfree(req->rl_rdmabuf);
out2:
	kfree(req);
out1:
	return NULL;
}