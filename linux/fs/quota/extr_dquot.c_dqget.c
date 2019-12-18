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
struct super_block {TYPE_1__* dq_op; int /*<<< orphan*/  s_user_ns; } ;
struct kqid {int /*<<< orphan*/  type; } ;
struct dquot {int /*<<< orphan*/  dq_sb; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  dq_count; struct kqid dq_id; } ;
struct TYPE_2__ {int (* acquire_dquot ) (struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DQST_CACHE_HITS ; 
 int /*<<< orphan*/  DQST_LOOKUPS ; 
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int EINVAL ; 
 struct dquot* ERR_PTR (int) ; 
 int ESRCH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_destroy_dquot (struct dquot*) ; 
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 
 int /*<<< orphan*/  dqstats_inc (int /*<<< orphan*/ ) ; 
 struct dquot* find_dquot (unsigned int,struct super_block*,struct kqid) ; 
 struct dquot* get_empty_dquot (struct super_block*,int /*<<< orphan*/ ) ; 
 unsigned int hashfn (struct super_block*,struct kqid) ; 
 int /*<<< orphan*/  insert_dquot_hash (struct dquot*) ; 
 int /*<<< orphan*/  put_inuse (struct dquot*) ; 
 int /*<<< orphan*/  qid_has_mapping (int /*<<< orphan*/ ,struct kqid) ; 
 int /*<<< orphan*/  remove_free_dquot (struct dquot*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dquot*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_dquot (struct dquot*) ; 

struct dquot *dqget(struct super_block *sb, struct kqid qid)
{
	unsigned int hashent = hashfn(sb, qid);
	struct dquot *dquot, *empty = NULL;

	if (!qid_has_mapping(sb->s_user_ns, qid))
		return ERR_PTR(-EINVAL);

        if (!sb_has_quota_active(sb, qid.type))
		return ERR_PTR(-ESRCH);
we_slept:
	spin_lock(&dq_list_lock);
	spin_lock(&dq_state_lock);
	if (!sb_has_quota_active(sb, qid.type)) {
		spin_unlock(&dq_state_lock);
		spin_unlock(&dq_list_lock);
		dquot = ERR_PTR(-ESRCH);
		goto out;
	}
	spin_unlock(&dq_state_lock);

	dquot = find_dquot(hashent, sb, qid);
	if (!dquot) {
		if (!empty) {
			spin_unlock(&dq_list_lock);
			empty = get_empty_dquot(sb, qid.type);
			if (!empty)
				schedule();	/* Try to wait for a moment... */
			goto we_slept;
		}
		dquot = empty;
		empty = NULL;
		dquot->dq_id = qid;
		/* all dquots go on the inuse_list */
		put_inuse(dquot);
		/* hash it first so it can be found */
		insert_dquot_hash(dquot);
		spin_unlock(&dq_list_lock);
		dqstats_inc(DQST_LOOKUPS);
	} else {
		if (!atomic_read(&dquot->dq_count))
			remove_free_dquot(dquot);
		atomic_inc(&dquot->dq_count);
		spin_unlock(&dq_list_lock);
		dqstats_inc(DQST_CACHE_HITS);
		dqstats_inc(DQST_LOOKUPS);
	}
	/* Wait for dq_lock - after this we know that either dquot_release() is
	 * already finished or it will be canceled due to dq_count > 1 test */
	wait_on_dquot(dquot);
	/* Read the dquot / allocate space in quota file */
	if (!test_bit(DQ_ACTIVE_B, &dquot->dq_flags)) {
		int err;

		err = sb->dq_op->acquire_dquot(dquot);
		if (err < 0) {
			dqput(dquot);
			dquot = ERR_PTR(err);
			goto out;
		}
	}
	/*
	 * Make sure following reads see filled structure - paired with
	 * smp_mb__before_atomic() in dquot_acquire().
	 */
	smp_rmb();
#ifdef CONFIG_QUOTA_DEBUG
	BUG_ON(!dquot->dq_sb);	/* Has somebody invalidated entry under us? */
#endif
out:
	if (empty)
		do_destroy_dquot(empty);

	return dquot;
}