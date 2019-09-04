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
struct zap_details {int dummy; } ;
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unmap_single_vma (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long,struct zap_details*) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 

__attribute__((used)) static void zap_page_range_single(struct vm_area_struct *vma, unsigned long address,
		unsigned long size, struct zap_details *details)
{
	struct mm_struct *mm = vma->vm_mm;
	struct mmu_gather tlb;
	unsigned long end = address + size;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm, address, end);
	update_hiwater_rss(mm);
	mmu_notifier_invalidate_range_start(mm, address, end);
	unmap_single_vma(&tlb, vma, address, end, details);
	mmu_notifier_invalidate_range_end(mm, address, end);
	tlb_finish_mmu(&tlb, address, end);
}