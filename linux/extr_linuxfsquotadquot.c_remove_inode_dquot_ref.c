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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 
 struct dquot** i_dquot (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_inode_dquot_ref(struct inode *inode, int type,
				   struct list_head *tofree_head)
{
	struct dquot **dquots = i_dquot(inode);
	struct dquot *dquot = dquots[type];

	if (!dquot)
		return;

	dquots[type] = NULL;
	if (list_empty(&dquot->dq_free)) {
		/*
		 * The inode still has reference to dquot so it can't be in the
		 * free list
		 */
		spin_lock(&dq_list_lock);
		list_add(&dquot->dq_free, tofree_head);
		spin_unlock(&dq_list_lock);
	} else {
		/*
		 * Dquot is already in a list to put so we won't drop the last
		 * reference here.
		 */
		dqput(dquot);
	}
}