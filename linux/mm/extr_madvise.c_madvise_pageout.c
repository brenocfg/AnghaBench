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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  can_do_pageout (struct vm_area_struct*) ; 
 int /*<<< orphan*/  can_madv_lru_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  madvise_pageout_page_range (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tlb_gather_mmu (struct mmu_gather*,struct mm_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static long madvise_pageout(struct vm_area_struct *vma,
			struct vm_area_struct **prev,
			unsigned long start_addr, unsigned long end_addr)
{
	struct mm_struct *mm = vma->vm_mm;
	struct mmu_gather tlb;

	*prev = vma;
	if (!can_madv_lru_vma(vma))
		return -EINVAL;

	if (!can_do_pageout(vma))
		return 0;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm, start_addr, end_addr);
	madvise_pageout_page_range(&tlb, vma, start_addr, end_addr);
	tlb_finish_mmu(&tlb, start_addr, end_addr);

	return 0;
}