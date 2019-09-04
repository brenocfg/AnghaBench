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
struct mmu_gather {int dummy; } ;
struct mm_walk {struct mmu_gather* private; int /*<<< orphan*/  mm; int /*<<< orphan*/  pmd_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  madvise_free_pte_range ; 
 int /*<<< orphan*/  tlb_end_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  tlb_start_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

__attribute__((used)) static void madvise_free_page_range(struct mmu_gather *tlb,
			     struct vm_area_struct *vma,
			     unsigned long addr, unsigned long end)
{
	struct mm_walk free_walk = {
		.pmd_entry = madvise_free_pte_range,
		.mm = vma->vm_mm,
		.private = tlb,
	};

	tlb_start_vma(tlb, vma);
	walk_page_range(addr, end, &free_walk);
	tlb_end_vma(tlb, vma);
}