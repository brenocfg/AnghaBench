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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int pgoff; struct page* page; TYPE_1__* vma; } ;
struct rchan_buf {scalar_t__ start; } ;
struct page {int dummy; } ;
typedef  int pgoff_t ;
struct TYPE_2__ {struct rchan_buf* vm_private_data; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* vmalloc_to_page (scalar_t__) ; 

__attribute__((used)) static vm_fault_t relay_buf_fault(struct vm_fault *vmf)
{
	struct page *page;
	struct rchan_buf *buf = vmf->vma->vm_private_data;
	pgoff_t pgoff = vmf->pgoff;

	if (!buf)
		return VM_FAULT_OOM;

	page = vmalloc_to_page(buf->start + (pgoff << PAGE_SHIFT));
	if (!page)
		return VM_FAULT_SIGBUS;
	get_page(page);
	vmf->page = page;

	return 0;
}