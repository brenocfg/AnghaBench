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
struct vm_area_struct {int /*<<< orphan*/  vm_file; struct vm_area_struct* vm_next; } ;
struct perf_addr_filter_range {int dummy; } ;
struct perf_addr_filter {int dummy; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;

/* Variables and functions */
 scalar_t__ perf_addr_filter_vma_adjust (struct perf_addr_filter*,struct vm_area_struct*,struct perf_addr_filter_range*) ; 

__attribute__((used)) static void perf_addr_filter_apply(struct perf_addr_filter *filter,
				   struct mm_struct *mm,
				   struct perf_addr_filter_range *fr)
{
	struct vm_area_struct *vma;

	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		if (!vma->vm_file)
			continue;

		if (perf_addr_filter_vma_adjust(filter, vma, fr))
			return;
	}
}