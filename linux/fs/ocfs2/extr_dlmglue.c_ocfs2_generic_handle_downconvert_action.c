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
struct ocfs2_lock_res {int l_flags; scalar_t__ l_blocking; scalar_t__ l_level; scalar_t__ l_requested; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DLM_LOCK_NL ; 
 int OCFS2_LOCK_ATTACHED ; 
 int OCFS2_LOCK_BLOCKED ; 
 int OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int) ; 
 scalar_t__ ocfs2_highest_compat_lock_level (scalar_t__) ; 

__attribute__((used)) static inline void ocfs2_generic_handle_downconvert_action(struct ocfs2_lock_res *lockres)
{
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BUSY));
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_ATTACHED));
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BLOCKED));
	BUG_ON(lockres->l_blocking <= DLM_LOCK_NL);

	lockres->l_level = lockres->l_requested;
	if (lockres->l_level <=
	    ocfs2_highest_compat_lock_level(lockres->l_blocking)) {
		lockres->l_blocking = DLM_LOCK_NL;
		lockres_clear_flags(lockres, OCFS2_LOCK_BLOCKED);
	}
	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
}