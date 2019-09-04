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
typedef  int vm_fault_t ;
struct vm_fault {unsigned int flags; TYPE_2__* vma; struct page* page; } ;
struct page {int /*<<< orphan*/  mapping; } ;
struct TYPE_4__ {TYPE_1__* vm_ops; } ;
struct TYPE_3__ {int (* page_mkwrite ) (struct vm_fault*) ;} ;

/* Variables and functions */
 int FAULT_FLAG_MKWRITE ; 
 int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_LOCKED ; 
 int VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int stub1 (struct vm_fault*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static vm_fault_t do_page_mkwrite(struct vm_fault *vmf)
{
	vm_fault_t ret;
	struct page *page = vmf->page;
	unsigned int old_flags = vmf->flags;

	vmf->flags = FAULT_FLAG_WRITE|FAULT_FLAG_MKWRITE;

	ret = vmf->vma->vm_ops->page_mkwrite(vmf);
	/* Restore original flags so that caller is not surprised */
	vmf->flags = old_flags;
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))
		return ret;
	if (unlikely(!(ret & VM_FAULT_LOCKED))) {
		lock_page(page);
		if (!page->mapping) {
			unlock_page(page);
			return 0; /* retry */
		}
		ret |= VM_FAULT_LOCKED;
	} else
		VM_BUG_ON_PAGE(!PageLocked(page), page);
	return ret;
}