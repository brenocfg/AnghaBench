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
struct ocfs2_mask_waiter {int mw_mask; int mw_goal; int /*<<< orphan*/  mw_complete; int /*<<< orphan*/  mw_item; } ;
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_track_lock_wait (struct ocfs2_lock_res*) ; 

__attribute__((used)) static int __lockres_remove_mask_waiter(struct ocfs2_lock_res *lockres,
				      struct ocfs2_mask_waiter *mw)
{
	int ret = 0;

	assert_spin_locked(&lockres->l_lock);
	if (!list_empty(&mw->mw_item)) {
		if ((lockres->l_flags & mw->mw_mask) != mw->mw_goal)
			ret = -EBUSY;

		list_del_init(&mw->mw_item);
		init_completion(&mw->mw_complete);
		ocfs2_track_lock_wait(lockres);
	}

	return ret;
}