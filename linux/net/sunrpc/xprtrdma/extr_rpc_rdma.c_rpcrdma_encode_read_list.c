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
struct xdr_stream {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  read_chunk_count; } ;
struct rpcrdma_xprt {TYPE_2__ rx_stats; } ;
struct rpcrdma_req {struct rpcrdma_mr_seg* rl_segments; struct xdr_stream rl_stream; } ;
struct rpcrdma_mr_seg {int dummy; } ;
struct rpcrdma_mr {scalar_t__ mr_nents; } ;
struct TYPE_6__ {TYPE_1__* head; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_task; TYPE_3__ rq_snd_buf; } ;
typedef  enum rpcrdma_chunktype { ____Placeholder_rpcrdma_chunktype } rpcrdma_chunktype ;
struct TYPE_4__ {unsigned int iov_len; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ IS_ERR (struct rpcrdma_mr_seg*) ; 
 int PTR_ERR (struct rpcrdma_mr_seg*) ; 
 int encode_item_not_present (struct xdr_stream*) ; 
 scalar_t__ encode_read_segment (struct xdr_stream*,struct rpcrdma_mr*,unsigned int) ; 
 int rpcrdma_areadch ; 
 int rpcrdma_convert_iovs (struct rpcrdma_xprt*,TYPE_3__*,unsigned int,int,struct rpcrdma_mr_seg*) ; 
 struct rpcrdma_mr_seg* rpcrdma_mr_prepare (struct rpcrdma_xprt*,struct rpcrdma_req*,struct rpcrdma_mr_seg*,int,int,struct rpcrdma_mr**) ; 
 int rpcrdma_noch ; 
 int /*<<< orphan*/  trace_xprtrdma_chunk_read (int /*<<< orphan*/ ,unsigned int,struct rpcrdma_mr*,int) ; 

__attribute__((used)) static int rpcrdma_encode_read_list(struct rpcrdma_xprt *r_xprt,
				    struct rpcrdma_req *req,
				    struct rpc_rqst *rqst,
				    enum rpcrdma_chunktype rtype)
{
	struct xdr_stream *xdr = &req->rl_stream;
	struct rpcrdma_mr_seg *seg;
	struct rpcrdma_mr *mr;
	unsigned int pos;
	int nsegs;

	if (rtype == rpcrdma_noch)
		goto done;

	pos = rqst->rq_snd_buf.head[0].iov_len;
	if (rtype == rpcrdma_areadch)
		pos = 0;
	seg = req->rl_segments;
	nsegs = rpcrdma_convert_iovs(r_xprt, &rqst->rq_snd_buf, pos,
				     rtype, seg);
	if (nsegs < 0)
		return nsegs;

	do {
		seg = rpcrdma_mr_prepare(r_xprt, req, seg, nsegs, false, &mr);
		if (IS_ERR(seg))
			return PTR_ERR(seg);

		if (encode_read_segment(xdr, mr, pos) < 0)
			return -EMSGSIZE;

		trace_xprtrdma_chunk_read(rqst->rq_task, pos, mr, nsegs);
		r_xprt->rx_stats.read_chunk_count++;
		nsegs -= mr->mr_nents;
	} while (nsegs);

done:
	return encode_item_not_present(xdr);
}