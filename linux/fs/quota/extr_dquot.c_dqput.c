#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t type; } ;
struct dquot {int /*<<< orphan*/  dq_free; int /*<<< orphan*/  dq_count; TYPE_2__* dq_sb; int /*<<< orphan*/  dq_flags; TYPE_4__ dq_id; } ;
struct TYPE_6__ {TYPE_1__* dq_op; } ;
struct TYPE_5__ {int (* write_dquot ) (struct dquot*) ;int /*<<< orphan*/  (* release_dquot ) (struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DQST_DROPS ; 
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_dquot_dirty (struct dquot*) ; 
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  dqstats_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ dquot_dirty (struct dquot*) ; 
 int /*<<< orphan*/  dquot_ref_wq ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,TYPE_4__) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dquot_last (struct dquot*) ; 
 int /*<<< orphan*/  quota_error (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/ * quotatypes ; 
 int /*<<< orphan*/  sb_has_quota_active (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dquot*) ; 
 int /*<<< orphan*/  stub2 (struct dquot*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dqput(struct dquot *dquot)
{
	int ret;

	if (!dquot)
		return;
#ifdef CONFIG_QUOTA_DEBUG
	if (!atomic_read(&dquot->dq_count)) {
		quota_error(dquot->dq_sb, "trying to free free dquot of %s %d",
			    quotatypes[dquot->dq_id.type],
			    from_kqid(&init_user_ns, dquot->dq_id));
		BUG();
	}
#endif
	dqstats_inc(DQST_DROPS);
we_slept:
	spin_lock(&dq_list_lock);
	if (atomic_read(&dquot->dq_count) > 1) {
		/* We have more than one user... nothing to do */
		atomic_dec(&dquot->dq_count);
		/* Releasing dquot during quotaoff phase? */
		if (!sb_has_quota_active(dquot->dq_sb, dquot->dq_id.type) &&
		    atomic_read(&dquot->dq_count) == 1)
			wake_up(&dquot_ref_wq);
		spin_unlock(&dq_list_lock);
		return;
	}
	/* Need to release dquot? */
	if (dquot_dirty(dquot)) {
		spin_unlock(&dq_list_lock);
		/* Commit dquot before releasing */
		ret = dquot->dq_sb->dq_op->write_dquot(dquot);
		if (ret < 0) {
			quota_error(dquot->dq_sb, "Can't write quota structure"
				    " (error %d). Quota may get out of sync!",
				    ret);
			/*
			 * We clear dirty bit anyway, so that we avoid
			 * infinite loop here
			 */
			clear_dquot_dirty(dquot);
		}
		goto we_slept;
	}
	if (test_bit(DQ_ACTIVE_B, &dquot->dq_flags)) {
		spin_unlock(&dq_list_lock);
		dquot->dq_sb->dq_op->release_dquot(dquot);
		goto we_slept;
	}
	atomic_dec(&dquot->dq_count);
#ifdef CONFIG_QUOTA_DEBUG
	/* sanity check */
	BUG_ON(!list_empty(&dquot->dq_free));
#endif
	put_dquot_last(dquot);
	spin_unlock(&dq_list_lock);
}