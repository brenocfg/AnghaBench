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
struct file_lock_list_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  hlist; } ;
struct file_lock {int /*<<< orphan*/  fl_link; int /*<<< orphan*/  fl_link_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_lock_list ; 
 int /*<<< orphan*/  file_rwsem ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_rwsem_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct file_lock_list_struct* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_insert_global_locks(struct file_lock *fl)
{
	struct file_lock_list_struct *fll = this_cpu_ptr(&file_lock_list);

	percpu_rwsem_assert_held(&file_rwsem);

	spin_lock(&fll->lock);
	fl->fl_link_cpu = smp_processor_id();
	hlist_add_head(&fl->fl_link, &fll->hlist);
	spin_unlock(&fll->lock);
}