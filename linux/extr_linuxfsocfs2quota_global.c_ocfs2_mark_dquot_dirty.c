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
struct super_block {int dummy; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct TYPE_6__ {int type; } ;
struct dquot {unsigned long dq_flags; int /*<<< orphan*/  dq_dqb_lock; TYPE_3__ dq_id; struct super_block* dq_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_5__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dqio_sem; } ;

/* Variables and functions */
 int DQ_LASTSET_B ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_QSYNC_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int QIF_BLIMITS_B ; 
 int QIF_BTIME_B ; 
 int QIF_ILIMITS_B ; 
 int QIF_INODES_B ; 
 int QIF_ITIME_B ; 
 int QIF_SPACE_B ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_3__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ journal_current_handle () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_local_write_dquot (struct dquot*) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_dquot (struct dquot*) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int ocfs2_write_dquot (struct dquot*) ; 
 TYPE_2__* sb_dqinfo (struct super_block*,int) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_mark_dquot_dirty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_mark_dquot_dirty(struct dquot *dquot)
{
	unsigned long mask = (1 << (DQ_LASTSET_B + QIF_ILIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BLIMITS_B)) |
			     (1 << (DQ_LASTSET_B + QIF_INODES_B)) |
			     (1 << (DQ_LASTSET_B + QIF_SPACE_B)) |
			     (1 << (DQ_LASTSET_B + QIF_BTIME_B)) |
			     (1 << (DQ_LASTSET_B + QIF_ITIME_B));
	int sync = 0;
	int status;
	struct super_block *sb = dquot->dq_sb;
	int type = dquot->dq_id.type;
	struct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;
	handle_t *handle;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	trace_ocfs2_mark_dquot_dirty(from_kqid(&init_user_ns, dquot->dq_id),
				     type);

	/* In case user set some limits, sync dquot immediately to global
	 * quota file so that information propagates quicker */
	spin_lock(&dquot->dq_dqb_lock);
	if (dquot->dq_flags & mask)
		sync = 1;
	spin_unlock(&dquot->dq_dqb_lock);
	/* This is a slight hack but we can't afford getting global quota
	 * lock if we already have a transaction started. */
	if (!sync || journal_current_handle()) {
		status = ocfs2_write_dquot(dquot);
		goto out;
	}
	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	handle = ocfs2_start_trans(osb, OCFS2_QSYNC_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}
	down_write(&sb_dqopt(sb)->dqio_sem);
	status = ocfs2_sync_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out_dlock;
	}
	/* Now write updated local dquot structure */
	status = ocfs2_local_write_dquot(dquot);
out_dlock:
	up_write(&sb_dqopt(sb)->dqio_sem);
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	if (status)
		mlog_errno(status);
	return status;
}