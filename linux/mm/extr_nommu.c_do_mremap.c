#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; TYPE_1__* vm_region; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {unsigned long vm_end; unsigned long vm_start; } ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 unsigned long EINVAL ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ EPERM ; 
 unsigned long MREMAP_FIXED ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int VM_MAYSHARE ; 
 TYPE_2__* current ; 
 struct vm_area_struct* find_vma_exact (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ offset_in_page (unsigned long) ; 

__attribute__((used)) static unsigned long do_mremap(unsigned long addr,
			unsigned long old_len, unsigned long new_len,
			unsigned long flags, unsigned long new_addr)
{
	struct vm_area_struct *vma;

	/* insanity checks first */
	old_len = PAGE_ALIGN(old_len);
	new_len = PAGE_ALIGN(new_len);
	if (old_len == 0 || new_len == 0)
		return (unsigned long) -EINVAL;

	if (offset_in_page(addr))
		return -EINVAL;

	if (flags & MREMAP_FIXED && new_addr != addr)
		return (unsigned long) -EINVAL;

	vma = find_vma_exact(current->mm, addr, old_len);
	if (!vma)
		return (unsigned long) -EINVAL;

	if (vma->vm_end != vma->vm_start + old_len)
		return (unsigned long) -EFAULT;

	if (vma->vm_flags & VM_MAYSHARE)
		return (unsigned long) -EPERM;

	if (new_len > vma->vm_region->vm_end - vma->vm_region->vm_start)
		return (unsigned long) -ENOMEM;

	/* all checks complete - do it */
	vma->vm_end = vma->vm_start + new_len;
	return vma->vm_start;
}