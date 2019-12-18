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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct gfs2_rbm {int bii; scalar_t__ offset; TYPE_1__* rgd; } ;
struct gfs2_inode {int /*<<< orphan*/  i_res; } ;
struct gfs2_extent {scalar_t__ len; struct gfs2_rbm rbm; } ;
struct gfs2_bitmap {int bi_offset; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_bytes; int /*<<< orphan*/ * bi_clone; struct buffer_head* bi_bh; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;
struct TYPE_2__ {int rd_length; scalar_t__ rd_extfail_pt; } ;

/* Variables and functions */
 scalar_t__ BFITNOENT ; 
 int E2BIG ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GBF_FULL ; 
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 int /*<<< orphan*/  GFS2_BLKST_UNLINKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ gfs2_bitfit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int gfs2_reservation_check_and_update (struct gfs2_rbm*,struct gfs2_inode const*,scalar_t__,struct gfs2_extent*) ; 
 int /*<<< orphan*/  gfs2_rs_active (int /*<<< orphan*/ *) ; 
 struct gfs2_bitmap* rbm_bi (struct gfs2_rbm*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_rbm_find(struct gfs2_rbm *rbm, u8 state, u32 *minext,
			 const struct gfs2_inode *ip, bool nowrap)
{
	bool scan_from_start = rbm->bii == 0 && rbm->offset == 0;
	struct buffer_head *bh;
	int last_bii;
	u32 offset;
	u8 *buffer;
	bool wrapped = false;
	int ret;
	struct gfs2_bitmap *bi;
	struct gfs2_extent maxext = { .rbm.rgd = rbm->rgd, };

	/*
	 * Determine the last bitmap to search.  If we're not starting at the
	 * beginning of a bitmap, we need to search that bitmap twice to scan
	 * the entire resource group.
	 */
	last_bii = rbm->bii - (rbm->offset == 0);

	while(1) {
		bi = rbm_bi(rbm);
		if ((ip == NULL || !gfs2_rs_active(&ip->i_res)) &&
		    test_bit(GBF_FULL, &bi->bi_flags) &&
		    (state == GFS2_BLKST_FREE))
			goto next_bitmap;

		bh = bi->bi_bh;
		buffer = bh->b_data + bi->bi_offset;
		WARN_ON(!buffer_uptodate(bh));
		if (state != GFS2_BLKST_UNLINKED && bi->bi_clone)
			buffer = bi->bi_clone + bi->bi_offset;
		offset = gfs2_bitfit(buffer, bi->bi_bytes, rbm->offset, state);
		if (offset == BFITNOENT) {
			if (state == GFS2_BLKST_FREE && rbm->offset == 0)
				set_bit(GBF_FULL, &bi->bi_flags);
			goto next_bitmap;
		}
		rbm->offset = offset;
		if (ip == NULL)
			return 0;

		ret = gfs2_reservation_check_and_update(rbm, ip,
							minext ? *minext : 0,
							&maxext);
		if (ret == 0)
			return 0;
		if (ret > 0)
			goto next_iter;
		if (ret == -E2BIG) {
			rbm->bii = 0;
			rbm->offset = 0;
			goto res_covered_end_of_rgrp;
		}
		return ret;

next_bitmap:	/* Find next bitmap in the rgrp */
		rbm->offset = 0;
		rbm->bii++;
		if (rbm->bii == rbm->rgd->rd_length)
			rbm->bii = 0;
res_covered_end_of_rgrp:
		if (rbm->bii == 0) {
			if (wrapped)
				break;
			wrapped = true;
			if (nowrap)
				break;
		}
next_iter:
		/* Have we scanned the entire resource group? */
		if (wrapped && rbm->bii > last_bii)
			break;
	}

	if (minext == NULL || state != GFS2_BLKST_FREE)
		return -ENOSPC;

	/* If the extent was too small, and it's smaller than the smallest
	   to have failed before, remember for future reference that it's
	   useless to search this rgrp again for this amount or more. */
	if (wrapped && (scan_from_start || rbm->bii > last_bii) &&
	    *minext < rbm->rgd->rd_extfail_pt)
		rbm->rgd->rd_extfail_pt = *minext;

	/* If the maximum extent we found is big enough to fulfill the
	   minimum requirements, use it anyway. */
	if (maxext.len) {
		*rbm = maxext.rbm;
		*minext = maxext.len;
		return 0;
	}

	return -ENOSPC;
}