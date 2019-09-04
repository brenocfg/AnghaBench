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
typedef  int vm_fault_t ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 unsigned int FAULT_FLAG_INSTRUCTION ; 
 unsigned int FAULT_FLAG_REMOTE ; 
 unsigned int FAULT_FLAG_USER ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  PGFAULT ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SIGSEGV ; 
 int __handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_vma_access_permitted (struct vm_area_struct*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  check_sync_rss_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_event_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int hugetlb_fault (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  mem_cgroup_enter_user_fault () ; 
 int /*<<< orphan*/  mem_cgroup_exit_user_fault () ; 
 int /*<<< orphan*/  mem_cgroup_oom_synchronize (int) ; 
 scalar_t__ task_in_memcg_oom (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

vm_fault_t handle_mm_fault(struct vm_area_struct *vma, unsigned long address,
		unsigned int flags)
{
	vm_fault_t ret;

	__set_current_state(TASK_RUNNING);

	count_vm_event(PGFAULT);
	count_memcg_event_mm(vma->vm_mm, PGFAULT);

	/* do counter updates before entering really critical section. */
	check_sync_rss_stat(current);

	if (!arch_vma_access_permitted(vma, flags & FAULT_FLAG_WRITE,
					    flags & FAULT_FLAG_INSTRUCTION,
					    flags & FAULT_FLAG_REMOTE))
		return VM_FAULT_SIGSEGV;

	/*
	 * Enable the memcg OOM handling for faults triggered in user
	 * space.  Kernel faults are handled more gracefully.
	 */
	if (flags & FAULT_FLAG_USER)
		mem_cgroup_enter_user_fault();

	if (unlikely(is_vm_hugetlb_page(vma)))
		ret = hugetlb_fault(vma->vm_mm, vma, address, flags);
	else
		ret = __handle_mm_fault(vma, address, flags);

	if (flags & FAULT_FLAG_USER) {
		mem_cgroup_exit_user_fault();
		/*
		 * The task may have entered a memcg OOM situation but
		 * if the allocation error was handled gracefully (no
		 * VM_FAULT_OOM), there is no need to kill anything.
		 * Just clean up the OOM state peacefully.
		 */
		if (task_in_memcg_oom(current) && !(ret & VM_FAULT_OOM))
			mem_cgroup_oom_synchronize(false);
	}

	return ret;
}