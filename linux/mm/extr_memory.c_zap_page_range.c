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
struct vm_area_struct {scalar_t__ vm_start; struct vm_area_struct* vm_next; int /*<<< orphan*/  vm_mm; } ;
struct mmu_notifier_range {scalar_t__ end; } ;
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  unmap_single_vma (struct mmu_gather*,struct vm_area_struct*,unsigned long,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_hiwater_rss (int /*<<< orphan*/ ) ; 

void zap_page_range(struct vm_area_struct *vma, unsigned long start,
		unsigned long size)
{
	struct mmu_notifier_range range;
	struct mmu_gather tlb;

	lru_add_drain();
	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				start, start + size);
	tlb_gather_mmu(&tlb, vma->vm_mm, start, range.end);
	update_hiwater_rss(vma->vm_mm);
	mmu_notifier_invalidate_range_start(&range);
	for ( ; vma && vma->vm_start < range.end; vma = vma->vm_next)
		unmap_single_vma(&tlb, vma, start, range.end, NULL);
	mmu_notifier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb, start, range.end);
}