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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {scalar_t__ dqb_rsvspace; int /*<<< orphan*/  dqb_curspace; } ;
struct dquot {int /*<<< orphan*/  dq_dqb_lock; TYPE_1__ dq_dqb; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int MAXQUOTAS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __inode_add_bytes (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  dquot_active (struct inode*) ; 
 int /*<<< orphan*/  dquot_srcu ; 
 struct dquot** i_dquot (struct inode*) ; 
 int /*<<< orphan*/ * inode_reserved_space (struct inode*) ; 
 int /*<<< orphan*/  mark_all_dquot_dirty (struct dquot**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

int dquot_claim_space_nodirty(struct inode *inode, qsize_t number)
{
	struct dquot **dquots;
	int cnt, index;

	if (!dquot_active(inode)) {
		spin_lock(&inode->i_lock);
		*inode_reserved_space(inode) -= number;
		__inode_add_bytes(inode, number);
		spin_unlock(&inode->i_lock);
		return 0;
	}

	dquots = i_dquot(inode);
	index = srcu_read_lock(&dquot_srcu);
	spin_lock(&inode->i_lock);
	/* Claim reserved quotas to allocated quotas */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquots[cnt]) {
			struct dquot *dquot = dquots[cnt];

			spin_lock(&dquot->dq_dqb_lock);
			if (WARN_ON_ONCE(dquot->dq_dqb.dqb_rsvspace < number))
				number = dquot->dq_dqb.dqb_rsvspace;
			dquot->dq_dqb.dqb_curspace += number;
			dquot->dq_dqb.dqb_rsvspace -= number;
			spin_unlock(&dquot->dq_dqb_lock);
		}
	}
	/* Update inode bytes */
	*inode_reserved_space(inode) -= number;
	__inode_add_bytes(inode, number);
	spin_unlock(&inode->i_lock);
	mark_all_dquot_dirty(dquots);
	srcu_read_unlock(&dquot_srcu, index);
	return 0;
}