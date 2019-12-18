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
struct ocfs2_lock_res {scalar_t__ l_blocking; int l_level; int l_requested; int /*<<< orphan*/  l_action; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_pending_gen; int /*<<< orphan*/  l_unlock_action; int /*<<< orphan*/  l_ex_holders; int /*<<< orphan*/  l_ro_holders; int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_mask_waiters; int /*<<< orphan*/  l_blocked_list; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DLM_LOCK_NL ; 
 int /*<<< orphan*/  ML_BASTS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_AST_DOWNCONVERT ; 
 int /*<<< orphan*/  OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 unsigned int lockres_set_pending (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,scalar_t__,...) ; 

__attribute__((used)) static unsigned int ocfs2_prepare_downconvert(struct ocfs2_lock_res *lockres,
					      int new_level)
{
	assert_spin_locked(&lockres->l_lock);

	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	if (lockres->l_level <= new_level) {
		mlog(ML_ERROR, "lockres %s, lvl %d <= %d, blcklst %d, mask %d, "
		     "type %d, flags 0x%lx, hold %d %d, act %d %d, req %d, "
		     "block %d, pgen %d\n", lockres->l_name, lockres->l_level,
		     new_level, list_empty(&lockres->l_blocked_list),
		     list_empty(&lockres->l_mask_waiters), lockres->l_type,
		     lockres->l_flags, lockres->l_ro_holders,
		     lockres->l_ex_holders, lockres->l_action,
		     lockres->l_unlock_action, lockres->l_requested,
		     lockres->l_blocking, lockres->l_pending_gen);
		BUG();
	}

	mlog(ML_BASTS, "lockres %s, level %d => %d, blocking %d\n",
	     lockres->l_name, lockres->l_level, new_level, lockres->l_blocking);

	lockres->l_action = OCFS2_AST_DOWNCONVERT;
	lockres->l_requested = new_level;
	lockres_or_flags(lockres, OCFS2_LOCK_BUSY);
	return lockres_set_pending(lockres);
}