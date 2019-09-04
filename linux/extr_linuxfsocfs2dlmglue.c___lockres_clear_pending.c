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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int l_flags; unsigned int l_pending_gen; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int OCFS2_LOCK_BLOCKED ; 
 int OCFS2_LOCK_PENDING ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_wake_downconvert_thread (struct ocfs2_super*) ; 

__attribute__((used)) static void __lockres_clear_pending(struct ocfs2_lock_res *lockres,
				    unsigned int generation,
				    struct ocfs2_super *osb)
{
	assert_spin_locked(&lockres->l_lock);

	/*
	 * The ast and locking functions can race us here.  The winner
	 * will clear pending, the loser will not.
	 */
	if (!(lockres->l_flags & OCFS2_LOCK_PENDING) ||
	    (lockres->l_pending_gen != generation))
		return;

	lockres_clear_flags(lockres, OCFS2_LOCK_PENDING);
	lockres->l_pending_gen++;

	/*
	 * The downconvert thread may have skipped us because we
	 * were PENDING.  Wake it up.
	 */
	if (lockres->l_flags & OCFS2_LOCK_BLOCKED)
		ocfs2_wake_downconvert_thread(osb);
}