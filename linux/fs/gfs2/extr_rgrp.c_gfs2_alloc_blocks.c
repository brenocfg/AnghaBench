#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rbm {TYPE_3__* rgd; } ;
struct TYPE_12__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_8__ {TYPE_3__* rgd; } ;
struct TYPE_11__ {TYPE_1__ rs_rbm; } ;
struct gfs2_inode {TYPE_7__ i_inode; scalar_t__ i_goal; int /*<<< orphan*/  i_gl; TYPE_4__ i_res; scalar_t__ i_no_addr; } ;
struct gfs2_dinode {int /*<<< orphan*/  di_goal_data; int /*<<< orphan*/  di_goal_meta; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_10__ {scalar_t__ rd_data0; unsigned int rd_free; unsigned int rd_free_clone; TYPE_2__* rd_bits; int /*<<< orphan*/  rd_gl; int /*<<< orphan*/  rd_igeneration; int /*<<< orphan*/  rd_dinodes; scalar_t__ rd_last_alloc; int /*<<< orphan*/  rd_extfail_pt; } ;
struct TYPE_9__ {struct buffer_head* bi_bh; int /*<<< orphan*/  bi_flags; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GBF_FULL ; 
 int /*<<< orphan*/  GFS2_BLKST_DINODE ; 
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 int /*<<< orphan*/  GFS2_BLKST_USED ; 
 struct gfs2_sbd* GFS2_SB (TYPE_7__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  gfs2_adjust_reservation (struct gfs2_inode*,struct gfs2_rbm*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_alloc_extent (struct gfs2_rbm*,int,unsigned int*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_quota_change (struct gfs2_inode*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_rbm_find (struct gfs2_rbm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gfs2_inode*,int) ; 
 scalar_t__ gfs2_rbm_to_block (struct gfs2_rbm*) ; 
 int /*<<< orphan*/  gfs2_rgrp_error (TYPE_3__*) ; 
 int /*<<< orphan*/  gfs2_rgrp_out (TYPE_3__*,scalar_t__) ; 
 scalar_t__ gfs2_rs_active (TYPE_4__*) ; 
 int /*<<< orphan*/  gfs2_set_alloc_start (struct gfs2_rbm*,struct gfs2_inode*,int) ; 
 int /*<<< orphan*/  gfs2_statfs_change (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_trans_remove_revoke (struct gfs2_sbd*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gfs2_block_alloc (struct gfs2_inode*,TYPE_3__*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

int gfs2_alloc_blocks(struct gfs2_inode *ip, u64 *bn, unsigned int *nblocks,
		      bool dinode, u64 *generation)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head *dibh;
	struct gfs2_rbm rbm = { .rgd = ip->i_res.rs_rbm.rgd, };
	unsigned int ndata;
	u64 block; /* block, within the file system scope */
	int error;

	gfs2_set_alloc_start(&rbm, ip, dinode);
	error = gfs2_rbm_find(&rbm, GFS2_BLKST_FREE, NULL, ip, false);

	if (error == -ENOSPC) {
		gfs2_set_alloc_start(&rbm, ip, dinode);
		error = gfs2_rbm_find(&rbm, GFS2_BLKST_FREE, NULL, NULL, false);
	}

	/* Since all blocks are reserved in advance, this shouldn't happen */
	if (error) {
		fs_warn(sdp, "inum=%llu error=%d, nblocks=%u, full=%d fail_pt=%d\n",
			(unsigned long long)ip->i_no_addr, error, *nblocks,
			test_bit(GBF_FULL, &rbm.rgd->rd_bits->bi_flags),
			rbm.rgd->rd_extfail_pt);
		goto rgrp_error;
	}

	gfs2_alloc_extent(&rbm, dinode, nblocks);
	block = gfs2_rbm_to_block(&rbm);
	rbm.rgd->rd_last_alloc = block - rbm.rgd->rd_data0;
	if (gfs2_rs_active(&ip->i_res))
		gfs2_adjust_reservation(ip, &rbm, *nblocks);
	ndata = *nblocks;
	if (dinode)
		ndata--;

	if (!dinode) {
		ip->i_goal = block + ndata - 1;
		error = gfs2_meta_inode_buffer(ip, &dibh);
		if (error == 0) {
			struct gfs2_dinode *di =
				(struct gfs2_dinode *)dibh->b_data;
			gfs2_trans_add_meta(ip->i_gl, dibh);
			di->di_goal_meta = di->di_goal_data =
				cpu_to_be64(ip->i_goal);
			brelse(dibh);
		}
	}
	if (rbm.rgd->rd_free < *nblocks) {
		fs_warn(sdp, "nblocks=%u\n", *nblocks);
		goto rgrp_error;
	}

	rbm.rgd->rd_free -= *nblocks;
	if (dinode) {
		rbm.rgd->rd_dinodes++;
		*generation = rbm.rgd->rd_igeneration++;
		if (*generation == 0)
			*generation = rbm.rgd->rd_igeneration++;
	}

	gfs2_trans_add_meta(rbm.rgd->rd_gl, rbm.rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rbm.rgd, rbm.rgd->rd_bits[0].bi_bh->b_data);

	gfs2_statfs_change(sdp, 0, -(s64)*nblocks, dinode ? 1 : 0);
	if (dinode)
		gfs2_trans_remove_revoke(sdp, block, *nblocks);

	gfs2_quota_change(ip, *nblocks, ip->i_inode.i_uid, ip->i_inode.i_gid);

	rbm.rgd->rd_free_clone -= *nblocks;
	trace_gfs2_block_alloc(ip, rbm.rgd, block, *nblocks,
			       dinode ? GFS2_BLKST_DINODE : GFS2_BLKST_USED);
	*bn = block;
	return 0;

rgrp_error:
	gfs2_rgrp_error(rbm.rgd);
	return -EIO;
}