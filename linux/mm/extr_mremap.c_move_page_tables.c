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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct mmu_notifier_range {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  MMU_NOTIFY_UNMAP ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 int /*<<< orphan*/ * alloc_new_pmd (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  drop_rmap_locks (struct vm_area_struct*) ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * get_old_pmd (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ is_swap_pmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int move_huge_pmd (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int move_normal_pmd (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_ptes (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 scalar_t__ pte_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  take_rmap_locks (struct vm_area_struct*) ; 

unsigned long move_page_tables(struct vm_area_struct *vma,
		unsigned long old_addr, struct vm_area_struct *new_vma,
		unsigned long new_addr, unsigned long len,
		bool need_rmap_locks)
{
	unsigned long extent, next, old_end;
	struct mmu_notifier_range range;
	pmd_t *old_pmd, *new_pmd;

	old_end = old_addr + len;
	flush_cache_range(vma, old_addr, old_end);

	mmu_notifier_range_init(&range, MMU_NOTIFY_UNMAP, 0, vma, vma->vm_mm,
				old_addr, old_end);
	mmu_notifier_invalidate_range_start(&range);

	for (; old_addr < old_end; old_addr += extent, new_addr += extent) {
		cond_resched();
		next = (old_addr + PMD_SIZE) & PMD_MASK;
		/* even if next overflowed, extent below will be ok */
		extent = next - old_addr;
		if (extent > old_end - old_addr)
			extent = old_end - old_addr;
		old_pmd = get_old_pmd(vma->vm_mm, old_addr);
		if (!old_pmd)
			continue;
		new_pmd = alloc_new_pmd(vma->vm_mm, vma, new_addr);
		if (!new_pmd)
			break;
		if (is_swap_pmd(*old_pmd) || pmd_trans_huge(*old_pmd)) {
			if (extent == HPAGE_PMD_SIZE) {
				bool moved;
				/* See comment in move_ptes() */
				if (need_rmap_locks)
					take_rmap_locks(vma);
				moved = move_huge_pmd(vma, old_addr, new_addr,
						    old_end, old_pmd, new_pmd);
				if (need_rmap_locks)
					drop_rmap_locks(vma);
				if (moved)
					continue;
			}
			split_huge_pmd(vma, old_pmd, old_addr);
			if (pmd_trans_unstable(old_pmd))
				continue;
		} else if (extent == PMD_SIZE) {
#ifdef CONFIG_HAVE_MOVE_PMD
			/*
			 * If the extent is PMD-sized, try to speed the move by
			 * moving at the PMD level if possible.
			 */
			bool moved;

			if (need_rmap_locks)
				take_rmap_locks(vma);
			moved = move_normal_pmd(vma, old_addr, new_addr,
					old_end, old_pmd, new_pmd);
			if (need_rmap_locks)
				drop_rmap_locks(vma);
			if (moved)
				continue;
#endif
		}

		if (pte_alloc(new_vma->vm_mm, new_pmd))
			break;
		next = (new_addr + PMD_SIZE) & PMD_MASK;
		if (extent > next - new_addr)
			extent = next - new_addr;
		move_ptes(vma, old_pmd, old_addr, old_addr + extent, new_vma,
			  new_pmd, new_addr, need_rmap_locks);
	}

	mmu_notifier_invalidate_range_end(&range);

	return len + old_addr - old_end;	/* how much done */
}