#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_mm; } ;
struct mm_walk {unsigned char* private; int /*<<< orphan*/  mm; int /*<<< orphan*/  hugetlb_entry; int /*<<< orphan*/  pte_hole; int /*<<< orphan*/  pmd_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 long ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mincore_hugetlb ; 
 int /*<<< orphan*/  mincore_pte_range ; 
 int /*<<< orphan*/  mincore_unmapped_range ; 
 int walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

__attribute__((used)) static long do_mincore(unsigned long addr, unsigned long pages, unsigned char *vec)
{
	struct vm_area_struct *vma;
	unsigned long end;
	int err;
	struct mm_walk mincore_walk = {
		.pmd_entry = mincore_pte_range,
		.pte_hole = mincore_unmapped_range,
		.hugetlb_entry = mincore_hugetlb,
		.private = vec,
	};

	vma = find_vma(current->mm, addr);
	if (!vma || addr < vma->vm_start)
		return -ENOMEM;
	mincore_walk.mm = vma->vm_mm;
	end = min(vma->vm_end, addr + (pages << PAGE_SHIFT));
	err = walk_page_range(addr, end, &mincore_walk);
	if (err < 0)
		return err;
	return (end - addr) >> PAGE_SHIFT;
}