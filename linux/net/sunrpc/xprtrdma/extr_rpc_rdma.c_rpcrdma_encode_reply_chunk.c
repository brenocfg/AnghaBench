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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_rdma_request; int /*<<< orphan*/  reply_chunk_count; } ;
struct rpcrdma_xprt {TYPE_1__ rx_stats; } ;
struct rpcrdma_req {struct rpcrdma_mr_seg* rl_segments; struct xdr_stream rl_stream; } ;
struct rpcrdma_mr_seg {int dummy; } ;
struct rpcrdma_mr {scalar_t__ mr_nents; scalar_t__ mr_length; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_task; int /*<<< orphan*/  rq_rcv_buf; } ;
typedef  enum rpcrdma_chunktype { ____Placeholder_rpcrdma_chunktype } rpcrdma_chunktype ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (struct rpcrdma_mr_seg*) ; 
 int PTR_ERR (struct rpcrdma_mr_seg*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int encode_item_not_present (struct xdr_stream*) ; 
 scalar_t__ encode_item_present (struct xdr_stream*) ; 
 scalar_t__ encode_rdma_segment (struct xdr_stream*,struct rpcrdma_mr*) ; 
 int rpcrdma_convert_iovs (struct rpcrdma_xprt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct rpcrdma_mr_seg*) ; 
 struct rpcrdma_mr_seg* rpcrdma_mr_prepare (struct rpcrdma_xprt*,struct rpcrdma_req*,struct rpcrdma_mr_seg*,int,int,struct rpcrdma_mr**) ; 
 int rpcrdma_replych ; 
 int /*<<< orphan*/  trace_xprtrdma_chunk_reply (int /*<<< orphan*/ ,struct rpcrdma_mr*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int rpcrdma_encode_reply_chunk(struct rpcrdma_xprt *r_xprt,
				      struct rpcrdma_req *req,
				      struct rpc_rqst *rqst,
				      enum rpcrdma_chunktype wtype)
{
	struct xdr_stream *xdr = &req->rl_stream;
	struct rpcrdma_mr_seg *seg;
	struct rpcrdma_mr *mr;
	int nsegs, nchunks;
	__be32 *segcount;

	if (wtype != rpcrdma_replych)
		return encode_item_not_present(xdr);

	seg = req->rl_segments;
	nsegs = rpcrdma_convert_iovs(r_xprt, &rqst->rq_rcv_buf, 0, wtype, seg);
	if (nsegs < 0)
		return nsegs;

	if (encode_item_present(xdr) < 0)
		return -EMSGSIZE;
	segcount = xdr_reserve_space(xdr, sizeof(*segcount));
	if (unlikely(!segcount))
		return -EMSGSIZE;
	/* Actual value encoded below */

	nchunks = 0;
	do {
		seg = rpcrdma_mr_prepare(r_xprt, req, seg, nsegs, true, &mr);
		if (IS_ERR(seg))
			return PTR_ERR(seg);

		if (encode_rdma_segment(xdr, mr) < 0)
			return -EMSGSIZE;

		trace_xprtrdma_chunk_reply(rqst->rq_task, mr, nsegs);
		r_xprt->rx_stats.reply_chunk_count++;
		r_xprt->rx_stats.total_rdma_request += mr->mr_length;
		nchunks++;
		nsegs -= mr->mr_nents;
	} while (nsegs);

	/* Update count of segments in the Reply chunk */
	*segcount = cpu_to_be32(nchunks);

	return 0;
}