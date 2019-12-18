#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {TYPE_1__* binfmt; int /*<<< orphan*/  mmlist; int /*<<< orphan*/  mm_users; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_aio (struct mm_struct*) ; 
 int /*<<< orphan*/  exit_mmap (struct mm_struct*) ; 
 int /*<<< orphan*/  khugepaged_exit (struct mm_struct*) ; 
 int /*<<< orphan*/  ksm_exit (struct mm_struct*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_put_huge_zero_page (struct mm_struct*) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  mmlist_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mm_exe_file (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobe_clear_state (struct mm_struct*) ; 

__attribute__((used)) static inline void __mmput(struct mm_struct *mm)
{
	VM_BUG_ON(atomic_read(&mm->mm_users));

	uprobe_clear_state(mm);
	exit_aio(mm);
	ksm_exit(mm);
	khugepaged_exit(mm); /* must run before exit_mmap */
	exit_mmap(mm);
	mm_put_huge_zero_page(mm);
	set_mm_exe_file(mm, NULL);
	if (!list_empty(&mm->mmlist)) {
		spin_lock(&mmlist_lock);
		list_del(&mm->mmlist);
		spin_unlock(&mmlist_lock);
	}
	if (mm->binfmt)
		module_put(mm->binfmt->module);
	mmdrop(mm);
}