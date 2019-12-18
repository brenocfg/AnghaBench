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
struct ocfs2_mask_waiter {unsigned long mw_mask; unsigned long mw_goal; int /*<<< orphan*/  mw_item; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_mask_waiters; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_track_lock_wait (struct ocfs2_lock_res*) ; 

__attribute__((used)) static void lockres_add_mask_waiter(struct ocfs2_lock_res *lockres,
				    struct ocfs2_mask_waiter *mw,
				    unsigned long mask,
				    unsigned long goal)
{
	BUG_ON(!list_empty(&mw->mw_item));

	assert_spin_locked(&lockres->l_lock);

	list_add_tail(&mw->mw_item, &lockres->l_mask_waiters);
	mw->mw_mask = mask;
	mw->mw_goal = goal;
	ocfs2_track_lock_wait(lockres);
}