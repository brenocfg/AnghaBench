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
struct file_lock_list_struct {int /*<<< orphan*/  lock; } ;
struct file_lock {int /*<<< orphan*/  fl_link; int /*<<< orphan*/  fl_link_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_lock_list ; 
 int /*<<< orphan*/  file_rwsem ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 struct file_lock_list_struct* per_cpu_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_rwsem_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_delete_global_locks(struct file_lock *fl)
{
	struct file_lock_list_struct *fll;

	percpu_rwsem_assert_held(&file_rwsem);

	/*
	 * Avoid taking lock if already unhashed. This is safe since this check
	 * is done while holding the flc_lock, and new insertions into the list
	 * also require that it be held.
	 */
	if (hlist_unhashed(&fl->fl_link))
		return;

	fll = per_cpu_ptr(&file_lock_list, fl->fl_link_cpu);
	spin_lock(&fll->lock);
	hlist_del_init(&fl->fl_link);
	spin_unlock(&fll->lock);
}