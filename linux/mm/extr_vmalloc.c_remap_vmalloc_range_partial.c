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
struct vm_struct {int flags; void* addr; } ;
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_ALIGNED (void*) ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_DMA_COHERENT ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_USERMAP ; 
 struct vm_struct* find_vm_area (void*) ; 
 int get_vm_area_size (struct vm_struct*) ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,struct page*) ; 
 struct page* vmalloc_to_page (void*) ; 

int remap_vmalloc_range_partial(struct vm_area_struct *vma, unsigned long uaddr,
				void *kaddr, unsigned long size)
{
	struct vm_struct *area;

	size = PAGE_ALIGN(size);

	if (!PAGE_ALIGNED(uaddr) || !PAGE_ALIGNED(kaddr))
		return -EINVAL;

	area = find_vm_area(kaddr);
	if (!area)
		return -EINVAL;

	if (!(area->flags & (VM_USERMAP | VM_DMA_COHERENT)))
		return -EINVAL;

	if (kaddr + size > area->addr + get_vm_area_size(area))
		return -EINVAL;

	do {
		struct page *page = vmalloc_to_page(kaddr);
		int ret;

		ret = vm_insert_page(vma, uaddr, page);
		if (ret)
			return ret;

		uaddr += PAGE_SIZE;
		kaddr += PAGE_SIZE;
		size -= PAGE_SIZE;
	} while (size > 0);

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	return 0;
}