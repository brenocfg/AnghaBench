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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {TYPE_2__* rd_rgl; TYPE_1__* rd_bits; int /*<<< orphan*/  rd_gl; } ;
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  b_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rl_unlinked; } ;
struct TYPE_4__ {TYPE_3__* bi_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_BLKST_UNLINKED ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_rgrp_out (struct gfs2_rgrpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  rgblk_free (struct gfs2_sbd*,struct gfs2_rgrpd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gfs2_block_alloc (struct gfs2_inode*,struct gfs2_rgrpd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void gfs2_unlink_di(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_rgrpd *rgd;
	u64 blkno = ip->i_no_addr;

	rgd = gfs2_blk2rgrpd(sdp, blkno, true);
	if (!rgd)
		return;
	rgblk_free(sdp, rgd, blkno, 1, GFS2_BLKST_UNLINKED);
	trace_gfs2_block_alloc(ip, rgd, blkno, 1, GFS2_BLKST_UNLINKED);
	gfs2_trans_add_meta(rgd->rd_gl, rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rgd, rgd->rd_bits[0].bi_bh->b_data);
	be32_add_cpu(&rgd->rd_rgl->rl_unlinked, 1);
}