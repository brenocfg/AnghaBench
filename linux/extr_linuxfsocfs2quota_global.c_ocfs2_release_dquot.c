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
struct ocfs2_super {scalar_t__ dc_task; int /*<<< orphan*/  dquot_drop_work; int /*<<< orphan*/  ocfs2_wq; int /*<<< orphan*/  dquot_drop_list; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct dquot {int /*<<< orphan*/  dq_lock; int /*<<< orphan*/  dq_flags; scalar_t__ dq_off; TYPE_2__ dq_id; int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_count; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_DQUOT (struct dquot*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  dqgrab (struct dquot*) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 scalar_t__ llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_calc_qdel_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_global_release_dquot (struct dquot*) ; 
 int ocfs2_local_release_dquot (int /*<<< orphan*/ *,struct dquot*) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_release_dquot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_release_dquot(struct dquot *dquot)
{
	handle_t *handle;
	struct ocfs2_mem_dqinfo *oinfo =
			sb_dqinfo(dquot->dq_sb, dquot->dq_id.type)->dqi_priv;
	struct ocfs2_super *osb = OCFS2_SB(dquot->dq_sb);
	int status = 0;

	trace_ocfs2_release_dquot(from_kqid(&init_user_ns, dquot->dq_id),
				  dquot->dq_id.type);

	mutex_lock(&dquot->dq_lock);
	/* Check whether we are not racing with some other dqget() */
	if (atomic_read(&dquot->dq_count) > 1)
		goto out;
	/* Running from downconvert thread? Postpone quota processing to wq */
	if (current == osb->dc_task) {
		/*
		 * Grab our own reference to dquot and queue it for delayed
		 * dropping.  Quota code rechecks after calling
		 * ->release_dquot() and won't free dquot structure.
		 */
		dqgrab(dquot);
		/* First entry on list -> queue work */
		if (llist_add(&OCFS2_DQUOT(dquot)->list, &osb->dquot_drop_list))
			queue_work(osb->ocfs2_wq, &osb->dquot_drop_work);
		goto out;
	}
	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	handle = ocfs2_start_trans(osb,
		ocfs2_calc_qdel_credits(dquot->dq_sb, dquot->dq_id.type));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_ilock;
	}

	status = ocfs2_global_release_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out_trans;
	}
	status = ocfs2_local_release_dquot(handle, dquot);
	/*
	 * If we fail here, we cannot do much as global structure is
	 * already released. So just complain...
	 */
	if (status < 0)
		mlog_errno(status);
	/*
	 * Clear dq_off so that we search for the structure in quota file next
	 * time we acquire it. The structure might be deleted and reallocated
	 * elsewhere by another node while our dquot structure is on freelist.
	 */
	dquot->dq_off = 0;
	clear_bit(DQ_ACTIVE_B, &dquot->dq_flags);
out_trans:
	ocfs2_commit_trans(osb, handle);
out_ilock:
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mutex_unlock(&dquot->dq_lock);
	if (status)
		mlog_errno(status);
	return status;
}