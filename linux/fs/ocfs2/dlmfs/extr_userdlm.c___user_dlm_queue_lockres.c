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
struct user_lock_res {int l_flags; int /*<<< orphan*/  l_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USER_LOCK_QUEUED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_dlm_grab_inode_ref (struct user_lock_res*) ; 
 int /*<<< orphan*/  user_dlm_unblock_lock ; 
 int /*<<< orphan*/  user_dlm_worker ; 

__attribute__((used)) static void __user_dlm_queue_lockres(struct user_lock_res *lockres)
{
	if (!(lockres->l_flags & USER_LOCK_QUEUED)) {
		user_dlm_grab_inode_ref(lockres);

		INIT_WORK(&lockres->l_work, user_dlm_unblock_lock);

		queue_work(user_dlm_worker, &lockres->l_work);
		lockres->l_flags |= USER_LOCK_QUEUED;
	}
}