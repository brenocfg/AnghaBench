#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int /*<<< orphan*/  i_lock; } ;
struct dquot_warn {int w_type; } ;
struct dquot {int /*<<< orphan*/  dq_dqb_lock; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 int QUOTA_NL_NOWARN ; 
 int /*<<< orphan*/  dquot_active (struct inode*) ; 
 int /*<<< orphan*/  dquot_decr_inodes (struct dquot* const,int) ; 
 int /*<<< orphan*/  dquot_srcu ; 
 int /*<<< orphan*/  flush_warnings (struct dquot_warn*) ; 
 struct dquot** i_dquot (struct inode*) ; 
 int info_idq_free (struct dquot* const,int) ; 
 int /*<<< orphan*/  mark_all_dquot_dirty (struct dquot* const*) ; 
 int /*<<< orphan*/  prepare_warning (struct dquot_warn*,struct dquot* const,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

void dquot_free_inode(struct inode *inode)
{
	unsigned int cnt;
	struct dquot_warn warn[MAXQUOTAS];
	struct dquot * const *dquots;
	int index;

	if (!dquot_active(inode))
		return;

	dquots = i_dquot(inode);
	index = srcu_read_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		int wtype;

		warn[cnt].w_type = QUOTA_NL_NOWARN;
		if (!dquots[cnt])
			continue;
		spin_lock(&dquots[cnt]->dq_dqb_lock);
		wtype = info_idq_free(dquots[cnt], 1);
		if (wtype != QUOTA_NL_NOWARN)
			prepare_warning(&warn[cnt], dquots[cnt], wtype);
		dquot_decr_inodes(dquots[cnt], 1);
		spin_unlock(&dquots[cnt]->dq_dqb_lock);
	}
	spin_unlock(&inode->i_lock);
	mark_all_dquot_dirty(dquots);
	srcu_read_unlock(&dquot_srcu, index);
	flush_warnings(warn);
}