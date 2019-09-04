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
typedef  int vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  page; struct vm_area_struct* vma; } ;
struct vm_area_struct {TYPE_1__* vm_ops; } ;
struct TYPE_2__ {scalar_t__ map_pages; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_RETRY ; 
 int __do_fault (struct vm_fault*) ; 
 int do_fault_around (struct vm_fault*) ; 
 int fault_around_bytes ; 
 int finish_fault (struct vm_fault*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t do_read_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	vm_fault_t ret = 0;

	/*
	 * Let's call ->map_pages() first and use ->fault() as fallback
	 * if page by the offset is not ready to be mapped (cold cache or
	 * something).
	 */
	if (vma->vm_ops->map_pages && fault_around_bytes >> PAGE_SHIFT > 1) {
		ret = do_fault_around(vmf);
		if (ret)
			return ret;
	}

	ret = __do_fault(vmf);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		return ret;

	ret |= finish_fault(vmf);
	unlock_page(vmf->page);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		put_page(vmf->page);
	return ret;
}