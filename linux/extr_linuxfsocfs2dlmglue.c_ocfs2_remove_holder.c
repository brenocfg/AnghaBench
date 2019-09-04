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
struct ocfs2_lock_res {int /*<<< orphan*/  l_lock; } ;
struct ocfs2_lock_holder {int /*<<< orphan*/  oh_owner_pid; int /*<<< orphan*/  oh_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_remove_holder(struct ocfs2_lock_res *lockres,
				       struct ocfs2_lock_holder *oh)
{
	spin_lock(&lockres->l_lock);
	list_del(&oh->oh_list);
	spin_unlock(&lockres->l_lock);

	put_pid(oh->oh_owner_pid);
}