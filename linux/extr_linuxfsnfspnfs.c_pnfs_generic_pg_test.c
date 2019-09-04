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
typedef  scalar_t__ u64 ;
struct nfs_pageio_descriptor {TYPE_2__* pg_lseg; } ;
struct nfs_page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {TYPE_1__ pls_range; } ;

/* Variables and functions */
 unsigned int nfs_generic_pg_test (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 
 scalar_t__ pnfs_end_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

size_t
pnfs_generic_pg_test(struct nfs_pageio_descriptor *pgio,
		     struct nfs_page *prev, struct nfs_page *req)
{
	unsigned int size;
	u64 seg_end, req_start, seg_left;

	size = nfs_generic_pg_test(pgio, prev, req);
	if (!size)
		return 0;

	/*
	 * 'size' contains the number of bytes left in the current page (up
	 * to the original size asked for in @req->wb_bytes).
	 *
	 * Calculate how many bytes are left in the layout segment
	 * and if there are less bytes than 'size', return that instead.
	 *
	 * Please also note that 'end_offset' is actually the offset of the
	 * first byte that lies outside the pnfs_layout_range. FIXME?
	 *
	 */
	if (pgio->pg_lseg) {
		seg_end = pnfs_end_offset(pgio->pg_lseg->pls_range.offset,
				     pgio->pg_lseg->pls_range.length);
		req_start = req_offset(req);

		/* start of request is past the last byte of this segment */
		if (req_start >= seg_end)
			return 0;

		/* adjust 'size' iff there are fewer bytes left in the
		 * segment than what nfs_generic_pg_test returned */
		seg_left = seg_end - req_start;
		if (seg_left < size)
			size = (unsigned int)seg_left;
	}

	return size;
}