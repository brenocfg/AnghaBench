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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct gfs2_trans {scalar_t__ tr_num_buf_new; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_thresh2; scalar_t__ sd_inptrs; } ;
struct gfs2_rgrpd {unsigned int rd_length; int /*<<< orphan*/  rd_gl; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct TYPE_9__ {struct gfs2_rgrpd* rgd; } ;
struct TYPE_10__ {TYPE_1__ rs_rbm; } ;
struct gfs2_inode {int /*<<< orphan*/  i_rw_mutex; int /*<<< orphan*/  i_gl; TYPE_4__ i_inode; scalar_t__ i_depth; TYPE_2__ i_res; } ;
struct gfs2_holder {int /*<<< orphan*/  gh_gl; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int s64 ;
typedef  scalar_t__ __be64 ;
struct TYPE_12__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_sbd* GFS2_SB (TYPE_4__*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 unsigned int RES_DINODE ; 
 unsigned int RES_INDIRECT ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  __gfs2_free_blocks (struct gfs2_inode*,struct gfs2_rgrpd*,scalar_t__,int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  current_time (TYPE_4__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (TYPE_4__*,int) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_get_inode_blocks (TYPE_4__*) ; 
 struct gfs2_rgrpd* gfs2_glock2rgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_is_locked_by_me (int /*<<< orphan*/ ) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 scalar_t__ gfs2_rs_active (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  rgrp_contains_block (struct gfs2_rgrpd*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sweep_bh_for_rgrps(struct gfs2_inode *ip, struct gfs2_holder *rd_gh,
			      struct buffer_head *bh, __be64 *start, __be64 *end,
			      bool meta, u32 *btotal)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_rgrpd *rgd;
	struct gfs2_trans *tr;
	__be64 *p;
	int blks_outside_rgrp;
	u64 bn, bstart, isize_blks;
	s64 blen; /* needs to be s64 or gfs2_add_inode_blocks breaks */
	int ret = 0;
	bool buf_in_tr = false; /* buffer was added to transaction */

more_rgrps:
	rgd = NULL;
	if (gfs2_holder_initialized(rd_gh)) {
		rgd = gfs2_glock2rgrp(rd_gh->gh_gl);
		gfs2_assert_withdraw(sdp,
			     gfs2_glock_is_locked_by_me(rd_gh->gh_gl));
	}
	blks_outside_rgrp = 0;
	bstart = 0;
	blen = 0;

	for (p = start; p < end; p++) {
		if (!*p)
			continue;
		bn = be64_to_cpu(*p);

		if (rgd) {
			if (!rgrp_contains_block(rgd, bn)) {
				blks_outside_rgrp++;
				continue;
			}
		} else {
			rgd = gfs2_blk2rgrpd(sdp, bn, true);
			if (unlikely(!rgd)) {
				ret = -EIO;
				goto out;
			}
			ret = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
						 0, rd_gh);
			if (ret)
				goto out;

			/* Must be done with the rgrp glock held: */
			if (gfs2_rs_active(&ip->i_res) &&
			    rgd == ip->i_res.rs_rbm.rgd)
				gfs2_rs_deltree(&ip->i_res);
		}

		/* The size of our transactions will be unknown until we
		   actually process all the metadata blocks that relate to
		   the rgrp. So we estimate. We know it can't be more than
		   the dinode's i_blocks and we don't want to exceed the
		   journal flush threshold, sd_log_thresh2. */
		if (current->journal_info == NULL) {
			unsigned int jblocks_rqsted, revokes;

			jblocks_rqsted = rgd->rd_length + RES_DINODE +
				RES_INDIRECT;
			isize_blks = gfs2_get_inode_blocks(&ip->i_inode);
			if (isize_blks > atomic_read(&sdp->sd_log_thresh2))
				jblocks_rqsted +=
					atomic_read(&sdp->sd_log_thresh2);
			else
				jblocks_rqsted += isize_blks;
			revokes = jblocks_rqsted;
			if (meta)
				revokes += end - start;
			else if (ip->i_depth)
				revokes += sdp->sd_inptrs;
			ret = gfs2_trans_begin(sdp, jblocks_rqsted, revokes);
			if (ret)
				goto out_unlock;
			down_write(&ip->i_rw_mutex);
		}
		/* check if we will exceed the transaction blocks requested */
		tr = current->journal_info;
		if (tr->tr_num_buf_new + RES_STATFS +
		    RES_QUOTA >= atomic_read(&sdp->sd_log_thresh2)) {
			/* We set blks_outside_rgrp to ensure the loop will
			   be repeated for the same rgrp, but with a new
			   transaction. */
			blks_outside_rgrp++;
			/* This next part is tricky. If the buffer was added
			   to the transaction, we've already set some block
			   pointers to 0, so we better follow through and free
			   them, or we will introduce corruption (so break).
			   This may be impossible, or at least rare, but I
			   decided to cover the case regardless.

			   If the buffer was not added to the transaction
			   (this call), doing so would exceed our transaction
			   size, so we need to end the transaction and start a
			   new one (so goto). */

			if (buf_in_tr)
				break;
			goto out_unlock;
		}

		gfs2_trans_add_meta(ip->i_gl, bh);
		buf_in_tr = true;
		*p = 0;
		if (bstart + blen == bn) {
			blen++;
			continue;
		}
		if (bstart) {
			__gfs2_free_blocks(ip, rgd, bstart, (u32)blen, meta);
			(*btotal) += blen;
			gfs2_add_inode_blocks(&ip->i_inode, -blen);
		}
		bstart = bn;
		blen = 1;
	}
	if (bstart) {
		__gfs2_free_blocks(ip, rgd, bstart, (u32)blen, meta);
		(*btotal) += blen;
		gfs2_add_inode_blocks(&ip->i_inode, -blen);
	}
out_unlock:
	if (!ret && blks_outside_rgrp) { /* If buffer still has non-zero blocks
					    outside the rgrp we just processed,
					    do it all over again. */
		if (current->journal_info) {
			struct buffer_head *dibh;

			ret = gfs2_meta_inode_buffer(ip, &dibh);
			if (ret)
				goto out;

			/* Every transaction boundary, we rewrite the dinode
			   to keep its di_blocks current in case of failure. */
			ip->i_inode.i_mtime = ip->i_inode.i_ctime =
				current_time(&ip->i_inode);
			gfs2_trans_add_meta(ip->i_gl, dibh);
			gfs2_dinode_out(ip, dibh->b_data);
			brelse(dibh);
			up_write(&ip->i_rw_mutex);
			gfs2_trans_end(sdp);
			buf_in_tr = false;
		}
		gfs2_glock_dq_uninit(rd_gh);
		cond_resched();
		goto more_rgrps;
	}
out:
	return ret;
}