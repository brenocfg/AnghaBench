#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_inode; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; int /*<<< orphan*/  qd_change_sync; TYPE_2__* qd_gl; } ;
struct gfs2_quota {int dummy; } ;
struct gfs2_inode {TYPE_2__* i_gl; int /*<<< orphan*/  i_inode; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; int /*<<< orphan*/  aflags; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_5__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GFS2_LFC_DO_SYNC ; 
 int GFS2_LOG_HEAD_FLUSH_NORMAL ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  QDF_REFRESH ; 
 unsigned int RES_DINODE ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  do_qc (struct gfs2_quota_data*,int /*<<< orphan*/ ) ; 
 int gfs2_adjust_quota (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_quota_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,TYPE_2__*,int) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 scalar_t__ gfs2_write_alloc_required (struct gfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gfs2_holder*) ; 
 struct gfs2_holder* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qd2offset (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort (struct gfs2_quota_data**,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_qd ; 

__attribute__((used)) static int do_sync(unsigned int num_qd, struct gfs2_quota_data **qda)
{
	struct gfs2_sbd *sdp = (*qda)->qd_gl->gl_name.ln_sbd;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	struct gfs2_alloc_parms ap = { .aflags = 0, };
	unsigned int data_blocks, ind_blocks;
	struct gfs2_holder *ghs, i_gh;
	unsigned int qx, x;
	struct gfs2_quota_data *qd;
	unsigned reserved;
	loff_t offset;
	unsigned int nalloc = 0, blocks;
	int error;

	error = gfs2_rsqa_alloc(ip);
	if (error)
		return error;

	gfs2_write_calc_reserv(ip, sizeof(struct gfs2_quota),
			      &data_blocks, &ind_blocks);

	ghs = kmalloc_array(num_qd, sizeof(struct gfs2_holder), GFP_NOFS);
	if (!ghs)
		return -ENOMEM;

	sort(qda, num_qd, sizeof(struct gfs2_quota_data *), sort_qd, NULL);
	inode_lock(&ip->i_inode);
	for (qx = 0; qx < num_qd; qx++) {
		error = gfs2_glock_nq_init(qda[qx]->qd_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &ghs[qx]);
		if (error)
			goto out;
	}

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &i_gh);
	if (error)
		goto out;

	for (x = 0; x < num_qd; x++) {
		offset = qd2offset(qda[x]);
		if (gfs2_write_alloc_required(ip, offset,
					      sizeof(struct gfs2_quota)))
			nalloc++;
	}

	/* 
	 * 1 blk for unstuffing inode if stuffed. We add this extra
	 * block to the reservation unconditionally. If the inode
	 * doesn't need unstuffing, the block will be released to the 
	 * rgrp since it won't be allocated during the transaction
	 */
	/* +3 in the end for unstuffing block, inode size update block
	 * and another block in case quota straddles page boundary and 
	 * two blocks need to be updated instead of 1 */
	blocks = num_qd * data_blocks + RES_DINODE + num_qd + 3;

	reserved = 1 + (nalloc * (data_blocks + ind_blocks));
	ap.target = reserved;
	error = gfs2_inplace_reserve(ip, &ap);
	if (error)
		goto out_alloc;

	if (nalloc)
		blocks += gfs2_rg_blocks(ip, reserved) + nalloc * ind_blocks + RES_STATFS;

	error = gfs2_trans_begin(sdp, blocks, 0);
	if (error)
		goto out_ipres;

	for (x = 0; x < num_qd; x++) {
		qd = qda[x];
		offset = qd2offset(qd);
		error = gfs2_adjust_quota(ip, offset, qd->qd_change_sync, qd, NULL);
		if (error)
			goto out_end_trans;

		do_qc(qd, -qd->qd_change_sync);
		set_bit(QDF_REFRESH, &qd->qd_flags);
	}

	error = 0;

out_end_trans:
	gfs2_trans_end(sdp);
out_ipres:
	gfs2_inplace_release(ip);
out_alloc:
	gfs2_glock_dq_uninit(&i_gh);
out:
	while (qx--)
		gfs2_glock_dq_uninit(&ghs[qx]);
	inode_unlock(&ip->i_inode);
	kfree(ghs);
	gfs2_log_flush(ip->i_gl->gl_name.ln_sbd, ip->i_gl,
		       GFS2_LOG_HEAD_FLUSH_NORMAL | GFS2_LFC_DO_SYNC);
	return error;
}