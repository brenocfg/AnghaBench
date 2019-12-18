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
struct ocfs2_lock_res {int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_holders; } ;
struct ocfs2_lock_holder {int /*<<< orphan*/  oh_list; int /*<<< orphan*/  oh_owner_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ocfs2_add_holder(struct ocfs2_lock_res *lockres,
				   struct ocfs2_lock_holder *oh)
{
	INIT_LIST_HEAD(&oh->oh_list);
	oh->oh_owner_pid = get_pid(task_pid(current));

	spin_lock(&lockres->l_lock);
	list_add_tail(&oh->oh_list, &lockres->l_holders);
	spin_unlock(&lockres->l_lock);
}