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
struct user_lock_res {int l_flags; int l_blocking; int /*<<< orphan*/  l_ex_holders; int /*<<< orphan*/  l_ro_holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 
 int USER_LOCK_BLOCKED ; 
 int /*<<< orphan*/  __user_dlm_queue_lockres (struct user_lock_res*) ; 

__attribute__((used)) static void __user_dlm_cond_queue_lockres(struct user_lock_res *lockres)
{
	int queue = 0;

	if (!(lockres->l_flags & USER_LOCK_BLOCKED))
		return;

	switch (lockres->l_blocking) {
	case DLM_LOCK_EX:
		if (!lockres->l_ex_holders && !lockres->l_ro_holders)
			queue = 1;
		break;
	case DLM_LOCK_PR:
		if (!lockres->l_ex_holders)
			queue = 1;
		break;
	default:
		BUG();
	}

	if (queue)
		__user_dlm_queue_lockres(lockres);
}