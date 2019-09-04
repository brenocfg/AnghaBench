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
struct vm_fault {TYPE_1__* vma; struct page* page; } ;
struct page {scalar_t__ mapping; int /*<<< orphan*/  index; } ;
struct inode {scalar_t__ i_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_LOCKED ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_update_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_wait_on_page_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static vm_fault_t fuse_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);

	file_update_time(vmf->vma->vm_file);
	lock_page(page);
	if (page->mapping != inode->i_mapping) {
		unlock_page(page);
		return VM_FAULT_NOPAGE;
	}

	fuse_wait_on_page_writeback(inode, page->index);
	return VM_FAULT_LOCKED;
}