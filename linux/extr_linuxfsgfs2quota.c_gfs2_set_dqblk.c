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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct qc_dqblk {int d_fieldmask; int d_spc_softlimit; int d_spc_hardlimit; int d_space; } ;
struct kqid {scalar_t__ type; } ;
struct TYPE_5__ {int sb_bsize_shift; } ;
struct TYPE_4__ {scalar_t__ ar_quota; } ;
struct gfs2_sbd {TYPE_2__ sd_sb; TYPE_1__ sd_args; int /*<<< orphan*/  sd_quota_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  qb_value; int /*<<< orphan*/  qb_limit; int /*<<< orphan*/  qb_warn; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; TYPE_3__ qd_qb; int /*<<< orphan*/  qd_gl; } ;
struct gfs2_quota {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; int /*<<< orphan*/  aflags; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int GFS2_FIELDMASK ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 scalar_t__ GFS2_QUOTA_OFF ; 
 scalar_t__ GRPQUOTA ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int QC_SPACE ; 
 int QC_SPC_HARD ; 
 int QC_SPC_SOFT ; 
 int /*<<< orphan*/  QDF_QMSG_QUIET ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ USRQUOTA ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gfs2_adjust_quota (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_quota_data*,struct qc_dqblk*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_write_alloc_required (struct gfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qd2offset (struct gfs2_quota_data*) ; 
 int qd_get (struct gfs2_sbd*,struct kqid,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int update_qd (struct gfs2_sbd*,struct gfs2_quota_data*) ; 

__attribute__((used)) static int gfs2_set_dqblk(struct super_block *sb, struct kqid qid,
			  struct qc_dqblk *fdq)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_quota_inode);
	struct gfs2_quota_data *qd;
	struct gfs2_holder q_gh, i_gh;
	unsigned int data_blocks, ind_blocks;
	unsigned int blocks = 0;
	int alloc_required;
	loff_t offset;
	int error;

	if (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF)
		return -ESRCH; /* Crazy XFS error code */

	if ((qid.type != USRQUOTA) &&
	    (qid.type != GRPQUOTA))
		return -EINVAL;

	if (fdq->d_fieldmask & ~GFS2_FIELDMASK)
		return -EINVAL;

	error = qd_get(sdp, qid, &qd);
	if (error)
		return error;

	error = gfs2_rsqa_alloc(ip);
	if (error)
		goto out_put;

	inode_lock(&ip->i_inode);
	error = gfs2_glock_nq_init(qd->qd_gl, LM_ST_EXCLUSIVE, 0, &q_gh);
	if (error)
		goto out_unlockput;
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &i_gh);
	if (error)
		goto out_q;

	/* Check for existing entry, if none then alloc new blocks */
	error = update_qd(sdp, qd);
	if (error)
		goto out_i;

	/* If nothing has changed, this is a no-op */
	if ((fdq->d_fieldmask & QC_SPC_SOFT) &&
	    ((fdq->d_spc_softlimit >> sdp->sd_sb.sb_bsize_shift) == be64_to_cpu(qd->qd_qb.qb_warn)))
		fdq->d_fieldmask ^= QC_SPC_SOFT;

	if ((fdq->d_fieldmask & QC_SPC_HARD) &&
	    ((fdq->d_spc_hardlimit >> sdp->sd_sb.sb_bsize_shift) == be64_to_cpu(qd->qd_qb.qb_limit)))
		fdq->d_fieldmask ^= QC_SPC_HARD;

	if ((fdq->d_fieldmask & QC_SPACE) &&
	    ((fdq->d_space >> sdp->sd_sb.sb_bsize_shift) == be64_to_cpu(qd->qd_qb.qb_value)))
		fdq->d_fieldmask ^= QC_SPACE;

	if (fdq->d_fieldmask == 0)
		goto out_i;

	offset = qd2offset(qd);
	alloc_required = gfs2_write_alloc_required(ip, offset, sizeof(struct gfs2_quota));
	if (gfs2_is_stuffed(ip))
		alloc_required = 1;
	if (alloc_required) {
		struct gfs2_alloc_parms ap = { .aflags = 0, };
		gfs2_write_calc_reserv(ip, sizeof(struct gfs2_quota),
				       &data_blocks, &ind_blocks);
		blocks = 1 + data_blocks + ind_blocks;
		ap.target = blocks;
		error = gfs2_inplace_reserve(ip, &ap);
		if (error)
			goto out_i;
		blocks += gfs2_rg_blocks(ip, blocks);
	}

	/* Some quotas span block boundaries and can update two blocks,
	   adding an extra block to the transaction to handle such quotas */
	error = gfs2_trans_begin(sdp, blocks + RES_DINODE + 2, 0);
	if (error)
		goto out_release;

	/* Apply changes */
	error = gfs2_adjust_quota(ip, offset, 0, qd, fdq);
	if (!error)
		clear_bit(QDF_QMSG_QUIET, &qd->qd_flags);

	gfs2_trans_end(sdp);
out_release:
	if (alloc_required)
		gfs2_inplace_release(ip);
out_i:
	gfs2_glock_dq_uninit(&i_gh);
out_q:
	gfs2_glock_dq_uninit(&q_gh);
out_unlockput:
	inode_unlock(&ip->i_inode);
out_put:
	qd_put(qd);
	return error;
}