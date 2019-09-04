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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; scalar_t__ vm_file; } ;
struct mm_struct {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t PAGE_ALIGN (size_t) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  delete_vma (struct mm_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  delete_vma_from_mm (struct vm_area_struct*) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int shrink_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 int split_vma (struct mm_struct*,struct vm_area_struct*,unsigned long,int) ; 

int do_munmap(struct mm_struct *mm, unsigned long start, size_t len, struct list_head *uf)
{
	struct vm_area_struct *vma;
	unsigned long end;
	int ret;

	len = PAGE_ALIGN(len);
	if (len == 0)
		return -EINVAL;

	end = start + len;

	/* find the first potentially overlapping VMA */
	vma = find_vma(mm, start);
	if (!vma) {
		static int limit;
		if (limit < 5) {
			pr_warn("munmap of memory not mmapped by process %d (%s): 0x%lx-0x%lx\n",
					current->pid, current->comm,
					start, start + len - 1);
			limit++;
		}
		return -EINVAL;
	}

	/* we're allowed to split an anonymous VMA but not a file-backed one */
	if (vma->vm_file) {
		do {
			if (start > vma->vm_start)
				return -EINVAL;
			if (end == vma->vm_end)
				goto erase_whole_vma;
			vma = vma->vm_next;
		} while (vma);
		return -EINVAL;
	} else {
		/* the chunk must be a subset of the VMA found */
		if (start == vma->vm_start && end == vma->vm_end)
			goto erase_whole_vma;
		if (start < vma->vm_start || end > vma->vm_end)
			return -EINVAL;
		if (offset_in_page(start))
			return -EINVAL;
		if (end != vma->vm_end && offset_in_page(end))
			return -EINVAL;
		if (start != vma->vm_start && end != vma->vm_end) {
			ret = split_vma(mm, vma, start, 1);
			if (ret < 0)
				return ret;
		}
		return shrink_vma(mm, vma, start, end);
	}

erase_whole_vma:
	delete_vma_from_mm(vma);
	delete_vma(mm, vma);
	return 0;
}