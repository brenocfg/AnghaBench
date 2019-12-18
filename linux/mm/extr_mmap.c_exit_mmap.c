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
struct vm_area_struct {int vm_flags; struct vm_area_struct* vm_next; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {struct vm_area_struct* mmap; scalar_t__ locked_vm; int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_USER_ADDRESS ; 
 int /*<<< orphan*/  MMF_OOM_SKIP ; 
 int /*<<< orphan*/  USER_PGTABLES_CEILING ; 
 int VM_ACCOUNT ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  __oom_reap_task_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  arch_exit_mmap (struct mm_struct*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_cache_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  free_pgtables (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mm_is_oom_victim (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_release (struct mm_struct*) ; 
 int /*<<< orphan*/  munlock_vma_pages_all (struct vm_area_struct*) ; 
 struct vm_area_struct* remove_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_vmas (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 scalar_t__ vma_pages (struct vm_area_struct*) ; 

void exit_mmap(struct mm_struct *mm)
{
	struct mmu_gather tlb;
	struct vm_area_struct *vma;
	unsigned long nr_accounted = 0;

	/* mm's last user has gone, and its about to be pulled down */
	mmu_notifier_release(mm);

	if (unlikely(mm_is_oom_victim(mm))) {
		/*
		 * Manually reap the mm to free as much memory as possible.
		 * Then, as the oom reaper does, set MMF_OOM_SKIP to disregard
		 * this mm from further consideration.  Taking mm->mmap_sem for
		 * write after setting MMF_OOM_SKIP will guarantee that the oom
		 * reaper will not run on this mm again after mmap_sem is
		 * dropped.
		 *
		 * Nothing can be holding mm->mmap_sem here and the above call
		 * to mmu_notifier_release(mm) ensures mmu notifier callbacks in
		 * __oom_reap_task_mm() will not block.
		 *
		 * This needs to be done before calling munlock_vma_pages_all(),
		 * which clears VM_LOCKED, otherwise the oom reaper cannot
		 * reliably test it.
		 */
		(void)__oom_reap_task_mm(mm);

		set_bit(MMF_OOM_SKIP, &mm->flags);
		down_write(&mm->mmap_sem);
		up_write(&mm->mmap_sem);
	}

	if (mm->locked_vm) {
		vma = mm->mmap;
		while (vma) {
			if (vma->vm_flags & VM_LOCKED)
				munlock_vma_pages_all(vma);
			vma = vma->vm_next;
		}
	}

	arch_exit_mmap(mm);

	vma = mm->mmap;
	if (!vma)	/* Can happen if dup_mmap() received an OOM */
		return;

	lru_add_drain();
	flush_cache_mm(mm);
	tlb_gather_mmu(&tlb, mm, 0, -1);
	/* update_hiwater_rss(mm) here? but nobody should be looking */
	/* Use -1 here to ensure all VMAs in the mm are unmapped */
	unmap_vmas(&tlb, vma, 0, -1);
	free_pgtables(&tlb, vma, FIRST_USER_ADDRESS, USER_PGTABLES_CEILING);
	tlb_finish_mmu(&tlb, 0, -1);

	/*
	 * Walk the list again, actually closing and freeing it,
	 * with preemption enabled, without holding any MM locks.
	 */
	while (vma) {
		if (vma->vm_flags & VM_ACCOUNT)
			nr_accounted += vma_pages(vma);
		vma = remove_vma(vma);
	}
	vm_unacct_memory(nr_accounted);
}