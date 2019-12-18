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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct mmu_notifier_range {int /*<<< orphan*/  end; } ;
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_single_vma (struct mmu_gather*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,struct zap_details*) ; 
 int /*<<< orphan*/  update_hiwater_rss (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zap_page_range_single(struct vm_area_struct *vma, unsigned long address,
		unsigned long size, struct zap_details *details)
{
	struct mmu_notifier_range range;
	struct mmu_gather tlb;

	lru_add_drain();
	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address, address + size);
	tlb_gather_mmu(&tlb, vma->vm_mm, address, range.end);
	update_hiwater_rss(vma->vm_mm);
	mmu_notifier_invalidate_range_start(&range);
	unmap_single_vma(&tlb, vma, address, range.end, details);
	mmu_notifier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb, address, range.end);
}