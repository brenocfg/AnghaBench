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
struct vm_area_struct {unsigned int vm_end; unsigned int vm_start; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int ksize (void const*) ; 
 unsigned int page_size (struct page*) ; 
 int /*<<< orphan*/  virt_addr_valid (void const*) ; 
 struct page* virt_to_head_page (void const*) ; 

unsigned int kobjsize(const void *objp)
{
	struct page *page;

	/*
	 * If the object we have should not have ksize performed on it,
	 * return size of 0
	 */
	if (!objp || !virt_addr_valid(objp))
		return 0;

	page = virt_to_head_page(objp);

	/*
	 * If the allocator sets PageSlab, we know the pointer came from
	 * kmalloc().
	 */
	if (PageSlab(page))
		return ksize(objp);

	/*
	 * If it's not a compound page, see if we have a matching VMA
	 * region. This test is intentionally done in reverse order,
	 * so if there's no VMA, we still fall through and hand back
	 * PAGE_SIZE for 0-order pages.
	 */
	if (!PageCompound(page)) {
		struct vm_area_struct *vma;

		vma = find_vma(current->mm, (unsigned long)objp);
		if (vma)
			return vma->vm_end - vma->vm_start;
	}

	/*
	 * The ksize() function is only guaranteed to work for pointers
	 * returned by kmalloc(). So handle arbitrary pointers here.
	 */
	return page_size(page);
}