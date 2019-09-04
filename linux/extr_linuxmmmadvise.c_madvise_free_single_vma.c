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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct mm_struct* vm_mm; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  madvise_free_page_range (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  vma_is_anonymous (struct vm_area_struct*) ; 

__attribute__((used)) static int madvise_free_single_vma(struct vm_area_struct *vma,
			unsigned long start_addr, unsigned long end_addr)
{
	unsigned long start, end;
	struct mm_struct *mm = vma->vm_mm;
	struct mmu_gather tlb;

	/* MADV_FREE works for only anon vma at the moment */
	if (!vma_is_anonymous(vma))
		return -EINVAL;

	start = max(vma->vm_start, start_addr);
	if (start >= vma->vm_end)
		return -EINVAL;
	end = min(vma->vm_end, end_addr);
	if (end <= vma->vm_start)
		return -EINVAL;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm, start, end);
	update_hiwater_rss(mm);

	mmu_notifier_invalidate_range_start(mm, start, end);
	madvise_free_page_range(&tlb, vma, start, end);
	mmu_notifier_invalidate_range_end(mm, start, end);
	tlb_finish_mmu(&tlb, start, end);

	return 0;
}