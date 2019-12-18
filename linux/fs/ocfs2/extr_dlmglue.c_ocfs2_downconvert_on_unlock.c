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
struct ocfs2_lock_res {int l_flags; int l_blocking; int /*<<< orphan*/  l_ex_holders; int /*<<< orphan*/  l_ro_holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 
 int OCFS2_LOCK_BLOCKED ; 
 int /*<<< orphan*/  ocfs2_wake_downconvert_thread (struct ocfs2_super*) ; 

__attribute__((used)) static void ocfs2_downconvert_on_unlock(struct ocfs2_super *osb,
					struct ocfs2_lock_res *lockres)
{
	int kick = 0;

	/* If we know that another node is waiting on our lock, kick
	 * the downconvert thread * pre-emptively when we reach a release
	 * condition. */
	if (lockres->l_flags & OCFS2_LOCK_BLOCKED) {
		switch(lockres->l_blocking) {
		case DLM_LOCK_EX:
			if (!lockres->l_ex_holders && !lockres->l_ro_holders)
				kick = 1;
			break;
		case DLM_LOCK_PR:
			if (!lockres->l_ex_holders)
				kick = 1;
			break;
		default:
			BUG();
		}
	}

	if (kick)
		ocfs2_wake_downconvert_thread(osb);
}