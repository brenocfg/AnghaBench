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
struct vm_area_struct {unsigned long vm_start; int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_end; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 long ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  can_do_mincore (struct vm_area_struct*) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,unsigned long) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mincore_walk_ops ; 
 int walk_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static long do_mincore(unsigned long addr, unsigned long pages, unsigned char *vec)
{
	struct vm_area_struct *vma;
	unsigned long end;
	int err;

	vma = find_vma(current->mm, addr);
	if (!vma || addr < vma->vm_start)
		return -ENOMEM;
	end = min(vma->vm_end, addr + (pages << PAGE_SHIFT));
	if (!can_do_mincore(vma)) {
		unsigned long pages = DIV_ROUND_UP(end - addr, PAGE_SIZE);
		memset(vec, 1, pages);
		return pages;
	}
	err = walk_page_range(vma->vm_mm, addr, end, &mincore_walk_ops, vec);
	if (err < 0)
		return err;
	return (end - addr) >> PAGE_SHIFT;
}