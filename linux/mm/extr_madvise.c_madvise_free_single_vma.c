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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; struct mm_struct* vm_mm; } ;
struct mmu_notifier_range {scalar_t__ start; scalar_t__ end; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMU_NOTIFY_CLEAR ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  madvise_free_walk_ops ; 
 scalar_t__ max (scalar_t__,unsigned long) ; 
 scalar_t__ min (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mmu_notifier_range*) ; 
 int /*<<< orphan*/  mmu_notifier_range_init (struct mmu_notifier_range*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,struct mm_struct*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tlb_end_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tlb_start_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  update_hiwater_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  vma_is_anonymous (struct vm_area_struct*) ; 
 int /*<<< orphan*/  walk_page_range (struct mm_struct*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,struct mmu_gather*) ; 

__attribute__((used)) static int madvise_free_single_vma(struct vm_area_struct *vma,
			unsigned long start_addr, unsigned long end_addr)
{
	struct mm_struct *mm = vma->vm_mm;
	struct mmu_notifier_range range;
	struct mmu_gather tlb;

	/* MADV_FREE works for only anon vma at the moment */
	if (!vma_is_anonymous(vma))
		return -EINVAL;

	range.start = max(vma->vm_start, start_addr);
	if (range.start >= vma->vm_end)
		return -EINVAL;
	range.end = min(vma->vm_end, end_addr);
	if (range.end <= vma->vm_start)
		return -EINVAL;
	mmu_notifier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				range.start, range.end);

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm, range.start, range.end);
	update_hiwater_rss(mm);

	mmu_notifier_invalidate_range_start(&range);
	tlb_start_vma(&tlb, vma);
	walk_page_range(vma->vm_mm, range.start, range.end,
			&madvise_free_walk_ops, &tlb);
	tlb_end_vma(&tlb, vma);
	mmu_notifier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb, range.start, range.end);

	return 0;
}