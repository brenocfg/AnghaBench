#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct rpcrdma_ia {int ri_max_frwr_depth; scalar_t__ ri_mrtype; TYPE_1__* ri_id; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct rpcrdma_mr_seg {scalar_t__ mr_len; scalar_t__ mr_offset; int /*<<< orphan*/  mr_page; } ;
struct ib_reg_wr {int key; int access; struct ib_mr* mr; } ;
struct TYPE_4__ {struct ib_reg_wr fr_regwr; struct ib_mr* fr_mr; } ;
struct rpcrdma_mr {int mr_nents; int mr_handle; int mr_offset; int /*<<< orphan*/  mr_dir; int /*<<< orphan*/  mr_length; TYPE_2__ frwr; int /*<<< orphan*/ * mr_sg; } ;
struct ib_mr {int iova; int rkey; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  EIO ; 
 struct rpcrdma_mr_seg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_MR_TYPE_SG_GAPS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ib_map_mr_sg (struct ib_mr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_update_fast_reg_key (struct ib_mr*,scalar_t__) ; 
 scalar_t__ offset_in_page (scalar_t__) ; 
 int /*<<< orphan*/  rpcrdma_data_dir (int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xprtrdma_frwr_maperr (struct rpcrdma_mr*,int) ; 
 int /*<<< orphan*/  trace_xprtrdma_frwr_sgerr (struct rpcrdma_mr*,int) ; 
 int /*<<< orphan*/  trace_xprtrdma_mr_map (struct rpcrdma_mr*) ; 
 scalar_t__ unlikely (int) ; 

struct rpcrdma_mr_seg *frwr_map(struct rpcrdma_xprt *r_xprt,
				struct rpcrdma_mr_seg *seg,
				int nsegs, bool writing, __be32 xid,
				struct rpcrdma_mr *mr)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	struct ib_reg_wr *reg_wr;
	struct ib_mr *ibmr;
	int i, n;
	u8 key;

	if (nsegs > ia->ri_max_frwr_depth)
		nsegs = ia->ri_max_frwr_depth;
	for (i = 0; i < nsegs;) {
		if (seg->mr_page)
			sg_set_page(&mr->mr_sg[i],
				    seg->mr_page,
				    seg->mr_len,
				    offset_in_page(seg->mr_offset));
		else
			sg_set_buf(&mr->mr_sg[i], seg->mr_offset,
				   seg->mr_len);

		++seg;
		++i;
		if (ia->ri_mrtype == IB_MR_TYPE_SG_GAPS)
			continue;
		if ((i < nsegs && offset_in_page(seg->mr_offset)) ||
		    offset_in_page((seg-1)->mr_offset + (seg-1)->mr_len))
			break;
	}
	mr->mr_dir = rpcrdma_data_dir(writing);

	mr->mr_nents =
		ib_dma_map_sg(ia->ri_id->device, mr->mr_sg, i, mr->mr_dir);
	if (!mr->mr_nents)
		goto out_dmamap_err;

	ibmr = mr->frwr.fr_mr;
	n = ib_map_mr_sg(ibmr, mr->mr_sg, mr->mr_nents, NULL, PAGE_SIZE);
	if (unlikely(n != mr->mr_nents))
		goto out_mapmr_err;

	ibmr->iova &= 0x00000000ffffffff;
	ibmr->iova |= ((u64)be32_to_cpu(xid)) << 32;
	key = (u8)(ibmr->rkey & 0x000000FF);
	ib_update_fast_reg_key(ibmr, ++key);

	reg_wr = &mr->frwr.fr_regwr;
	reg_wr->mr = ibmr;
	reg_wr->key = ibmr->rkey;
	reg_wr->access = writing ?
			 IB_ACCESS_REMOTE_WRITE | IB_ACCESS_LOCAL_WRITE :
			 IB_ACCESS_REMOTE_READ;

	mr->mr_handle = ibmr->rkey;
	mr->mr_length = ibmr->length;
	mr->mr_offset = ibmr->iova;
	trace_xprtrdma_mr_map(mr);

	return seg;

out_dmamap_err:
	mr->mr_dir = DMA_NONE;
	trace_xprtrdma_frwr_sgerr(mr, i);
	return ERR_PTR(-EIO);

out_mapmr_err:
	trace_xprtrdma_frwr_maperr(mr, n);
	return ERR_PTR(-EIO);
}