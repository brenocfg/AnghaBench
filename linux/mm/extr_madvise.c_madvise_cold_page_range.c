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
struct madvise_walk_private {int pageout; struct mmu_gather* tlb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cold_walk_ops ; 
 int /*<<< orphan*/  tlb_end_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  tlb_start_vma (struct mmu_gather*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  walk_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *,struct madvise_walk_private*) ; 

__attribute__((used)) static void madvise_cold_page_range(struct mmu_gather *tlb,
			     struct vm_area_struct *vma,
			     unsigned long addr, unsigned long end)
{
	struct madvise_walk_private walk_private = {
		.pageout = false,
		.tlb = tlb,
	};

	tlb_start_vma(tlb, vma);
	walk_page_range(vma->vm_mm, addr, end, &cold_walk_ops, &walk_private);
	tlb_end_vma(tlb, vma);
}