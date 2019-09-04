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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int /*<<< orphan*/  ri_device; } ;
struct rpcrdma_xprt {TYPE_1__ rx_ia; } ;
struct rpcrdma_mr_seg {int mr_offset; int mr_len; int /*<<< orphan*/  mr_page; } ;
struct TYPE_5__ {TYPE_3__* fm_mr; scalar_t__* fm_physaddrs; } ;
struct rpcrdma_mr {int mr_nents; int mr_length; int /*<<< orphan*/ * mr_sg; scalar_t__ mr_offset; TYPE_2__ fmr; int /*<<< orphan*/  mr_handle; int /*<<< orphan*/  mr_dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 struct rpcrdma_mr_seg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int RPCRDMA_MAX_FMR_SGES ; 
 int ib_dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ib_map_phys_fmr (TYPE_3__*,scalar_t__*,int,scalar_t__) ; 
 int offset_in_page (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,unsigned long long,...) ; 
 int /*<<< orphan*/  rpcrdma_data_dir (int) ; 
 struct rpcrdma_mr* rpcrdma_mr_get (struct rpcrdma_xprt*) ; 
 int /*<<< orphan*/  rpcrdma_mr_put (struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  rpcrdma_mr_unmap_and_put (struct rpcrdma_mr*) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_xprtrdma_dma_map (struct rpcrdma_mr*) ; 

__attribute__((used)) static struct rpcrdma_mr_seg *
fmr_op_map(struct rpcrdma_xprt *r_xprt, struct rpcrdma_mr_seg *seg,
	   int nsegs, bool writing, struct rpcrdma_mr **out)
{
	struct rpcrdma_mr_seg *seg1 = seg;
	int len, pageoff, i, rc;
	struct rpcrdma_mr *mr;
	u64 *dma_pages;

	mr = rpcrdma_mr_get(r_xprt);
	if (!mr)
		return ERR_PTR(-EAGAIN);

	pageoff = offset_in_page(seg1->mr_offset);
	seg1->mr_offset -= pageoff;	/* start of page */
	seg1->mr_len += pageoff;
	len = -pageoff;
	if (nsegs > RPCRDMA_MAX_FMR_SGES)
		nsegs = RPCRDMA_MAX_FMR_SGES;
	for (i = 0; i < nsegs;) {
		if (seg->mr_page)
			sg_set_page(&mr->mr_sg[i],
				    seg->mr_page,
				    seg->mr_len,
				    offset_in_page(seg->mr_offset));
		else
			sg_set_buf(&mr->mr_sg[i], seg->mr_offset,
				   seg->mr_len);
		len += seg->mr_len;
		++seg;
		++i;
		/* Check for holes */
		if ((i < nsegs && offset_in_page(seg->mr_offset)) ||
		    offset_in_page((seg-1)->mr_offset + (seg-1)->mr_len))
			break;
	}
	mr->mr_dir = rpcrdma_data_dir(writing);

	mr->mr_nents = ib_dma_map_sg(r_xprt->rx_ia.ri_device,
				     mr->mr_sg, i, mr->mr_dir);
	if (!mr->mr_nents)
		goto out_dmamap_err;
	trace_xprtrdma_dma_map(mr);

	for (i = 0, dma_pages = mr->fmr.fm_physaddrs; i < mr->mr_nents; i++)
		dma_pages[i] = sg_dma_address(&mr->mr_sg[i]);
	rc = ib_map_phys_fmr(mr->fmr.fm_mr, dma_pages, mr->mr_nents,
			     dma_pages[0]);
	if (rc)
		goto out_maperr;

	mr->mr_handle = mr->fmr.fm_mr->rkey;
	mr->mr_length = len;
	mr->mr_offset = dma_pages[0] + pageoff;

	*out = mr;
	return seg;

out_dmamap_err:
	pr_err("rpcrdma: failed to DMA map sg %p sg_nents %d\n",
	       mr->mr_sg, i);
	rpcrdma_mr_put(mr);
	return ERR_PTR(-EIO);

out_maperr:
	pr_err("rpcrdma: ib_map_phys_fmr %u@0x%llx+%i (%d) status %i\n",
	       len, (unsigned long long)dma_pages[0],
	       pageoff, mr->mr_nents, rc);
	rpcrdma_mr_unmap_and_put(mr);
	return ERR_PTR(-EIO);
}