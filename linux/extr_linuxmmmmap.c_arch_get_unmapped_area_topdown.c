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
struct vm_unmapped_area_info {unsigned long length; unsigned long high_limit; int /*<<< orphan*/  low_limit; scalar_t__ flags; scalar_t__ align_mask; } ;
struct vm_area_struct {int dummy; } ;
struct mm_struct {unsigned long mmap_base; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 unsigned long const MAP_FIXED ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long const TASK_SIZE ; 
 int /*<<< orphan*/  TASK_UNMAPPED_BASE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 scalar_t__ VM_UNMAPPED_AREA_TOPDOWN ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma_prev (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned long const) ; 
 unsigned long const mmap_min_addr ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 unsigned long vm_end_gap (struct vm_area_struct*) ; 
 unsigned long vm_start_gap (struct vm_area_struct*) ; 
 unsigned long vm_unmapped_area (struct vm_unmapped_area_info*) ; 

unsigned long
arch_get_unmapped_area_topdown(struct file *filp, const unsigned long addr0,
			  const unsigned long len, const unsigned long pgoff,
			  const unsigned long flags)
{
	struct vm_area_struct *vma, *prev;
	struct mm_struct *mm = current->mm;
	unsigned long addr = addr0;
	struct vm_unmapped_area_info info;

	/* requested length too big for entire address space */
	if (len > TASK_SIZE - mmap_min_addr)
		return -ENOMEM;

	if (flags & MAP_FIXED)
		return addr;

	/* requesting a specific address */
	if (addr) {
		addr = PAGE_ALIGN(addr);
		vma = find_vma_prev(mm, addr, &prev);
		if (TASK_SIZE - len >= addr && addr >= mmap_min_addr &&
				(!vma || addr + len <= vm_start_gap(vma)) &&
				(!prev || addr >= vm_end_gap(prev)))
			return addr;
	}

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = mm->mmap_base;
	info.align_mask = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	if (offset_in_page(addr)) {
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
	}

	return addr;
}