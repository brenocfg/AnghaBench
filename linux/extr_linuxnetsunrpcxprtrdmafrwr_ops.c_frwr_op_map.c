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
typedef  scalar_t__ u8 ;
struct rpcrdma_ia {scalar_t__ ri_mrtype; int ri_max_frwr_depth; int /*<<< orphan*/  ri_device; } ;
struct rpcrdma_xprt {struct rpcrdma_ia rx_ia; } ;
struct rpcrdma_mr_seg {scalar_t__ mr_len; scalar_t__ mr_offset; int /*<<< orphan*/  mr_page; } ;
struct ib_reg_wr {int key; int access; struct ib_mr* mr; } ;
struct rpcrdma_frwr {scalar_t__ fr_state; struct ib_mr* fr_mr; struct ib_reg_wr fr_regwr; } ;
struct rpcrdma_mr {int mr_nents; int mr_handle; int /*<<< orphan*/ * mr_sg; int /*<<< orphan*/  mr_offset; int /*<<< orphan*/  mr_length; int /*<<< orphan*/  mr_dir; struct rpcrdma_frwr frwr; } ;
struct ib_mr {int rkey; int /*<<< orphan*/  iova; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 struct rpcrdma_mr_seg* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ FRWR_IS_INVALID ; 
 scalar_t__ FRWR_IS_VALID ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_MR_TYPE_SG_GAPS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ib_dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ib_map_mr_sg (struct ib_mr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_update_fast_reg_key (struct ib_mr*,scalar_t__) ; 
 scalar_t__ offset_in_page (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,struct ib_mr*,int,...) ; 
 int /*<<< orphan*/  rpcrdma_data_dir (int) ; 
 int /*<<< orphan*/  rpcrdma_mr_defer_recovery (struct rpcrdma_mr*) ; 
 struct rpcrdma_mr* rpcrdma_mr_get (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  rpcrdma_mr_put (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xprtrdma_dma_map (struct rpcrdma_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct rpcrdma_mr_seg *
frwr_op_map(struct rpcrdma_xprt *r_xprt, struct rpcrdma_mr_seg *seg,
	    int nsegs, bool writing, struct rpcrdma_mr **out)
{
	struct rpcrdma_ia *ia = &r_xprt->rx_ia;
	bool holes_ok = ia->ri_mrtype == IB_MR_TYPE_SG_GAPS;
	struct rpcrdma_frwr *frwr;
	struct rpcrdma_mr *mr;
	struct ib_mr *ibmr;
	struct ib_reg_wr *reg_wr;
	int i, n;
	u8 key;

	mr = NULL;
	do {
		if (mr)
			rpcrdma_mr_defer_recovery(mr);
		mr = rpcrdma_mr_get(r_xprt);
		if (!mr)
			return ERR_PTR(-EAGAIN);
	} while (mr->frwr.fr_state != FRWR_IS_INVALID);
	frwr = &mr->frwr;
	frwr->fr_state = FRWR_IS_VALID;

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
		if (holes_ok)
			continue;
		if ((i < nsegs && offset_in_page(seg->mr_offset)) ||
		    offset_in_page((seg-1)->mr_offset + (seg-1)->mr_len))
			break;
	}
	mr->mr_dir = rpcrdma_data_dir(writing);

	mr->mr_nents = ib_dma_map_sg(ia->ri_device, mr->mr_sg, i, mr->mr_dir);
	if (!mr->mr_nents)
		goto out_dmamap_err;
	trace_xprtrdma_dma_map(mr);

	ibmr = frwr->fr_mr;
	n = ib_map_mr_sg(ibmr, mr->mr_sg, mr->mr_nents, NULL, PAGE_SIZE);
	if (unlikely(n != mr->mr_nents))
		goto out_mapmr_err;

	key = (u8)(ibmr->rkey & 0x000000FF);
	ib_update_fast_reg_key(ibmr, ++key);

	reg_wr = &frwr->fr_regwr;
	reg_wr->mr = ibmr;
	reg_wr->key = ibmr->rkey;
	reg_wr->access = writing ?
			 IB_ACCESS_REMOTE_WRITE | IB_ACCESS_LOCAL_WRITE :
			 IB_ACCESS_REMOTE_READ;

	mr->mr_handle = ibmr->rkey;
	mr->mr_length = ibmr->length;
	mr->mr_offset = ibmr->iova;

	*out = mr;
	return seg;

out_dmamap_err:
	pr_err("rpcrdma: failed to DMA map sg %p sg_nents %d\n",
	       mr->mr_sg, i);
	frwr->fr_state = FRWR_IS_INVALID;
	rpcrdma_mr_put(mr);
	return ERR_PTR(-EIO);

out_mapmr_err:
	pr_err("rpcrdma: failed to map mr %p (%d/%d)\n",
	       frwr->fr_mr, n, mr->mr_nents);
	rpcrdma_mr_defer_recovery(mr);
	return ERR_PTR(-EIO);
}