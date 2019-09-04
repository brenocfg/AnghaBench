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
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; struct file* vm_file; struct vm_area_struct* vm_next; } ;
struct perf_addr_filter {int dummy; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  perf_addr_filter_match (struct perf_addr_filter*,struct file*,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long perf_addr_filter_apply(struct perf_addr_filter *filter,
					    struct mm_struct *mm)
{
	struct vm_area_struct *vma;

	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		struct file *file = vma->vm_file;
		unsigned long off = vma->vm_pgoff << PAGE_SHIFT;
		unsigned long vma_size = vma->vm_end - vma->vm_start;

		if (!file)
			continue;

		if (!perf_addr_filter_match(filter, file, off, vma_size))
			continue;

		return vma->vm_start;
	}

	return 0;
}