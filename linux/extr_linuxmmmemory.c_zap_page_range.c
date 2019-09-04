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
struct vm_area_struct {unsigned long vm_start; struct vm_area_struct* vm_next; struct mm_struct* vm_mm; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unmap_single_vma (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 

void zap_page_range(struct vm_area_struct *vma, unsigned long start,
		unsigned long size)
{
	struct mm_struct *mm = vma->vm_mm;
	struct mmu_gather tlb;
	unsigned long end = start + size;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm, start, end);
	update_hiwater_rss(mm);
	mmu_notifier_invalidate_range_start(mm, start, end);
	for ( ; vma && vma->vm_start < end; vma = vma->vm_next)
		unmap_single_vma(&tlb, vma, start, end, NULL);
	mmu_notifier_invalidate_range_end(mm, start, end);
	tlb_finish_mmu(&tlb, start, end);
}