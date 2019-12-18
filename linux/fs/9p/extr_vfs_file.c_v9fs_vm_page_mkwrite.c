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
struct v9fs_inode {int /*<<< orphan*/  writeback_fid; } ;
struct page {scalar_t__ mapping; } ;
struct inode {scalar_t__ i_mapping; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_2__ {struct file* vm_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  VM_FAULT_LOCKED ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct page*,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  v9fs_fscache_wait_on_page_write (struct inode*,struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

__attribute__((used)) static vm_fault_t
v9fs_vm_page_mkwrite(struct vm_fault *vmf)
{
	struct v9fs_inode *v9inode;
	struct page *page = vmf->page;
	struct file *filp = vmf->vma->vm_file;
	struct inode *inode = file_inode(filp);


	p9_debug(P9_DEBUG_VFS, "page %p fid %lx\n",
		 page, (unsigned long)filp->private_data);

	/* Update file times before taking page lock */
	file_update_time(filp);

	v9inode = V9FS_I(inode);
	/* make sure the cache has finished storing the page */
	v9fs_fscache_wait_on_page_write(inode, page);
	BUG_ON(!v9inode->writeback_fid);
	lock_page(page);
	if (page->mapping != inode->i_mapping)
		goto out_unlock;
	wait_for_stable_page(page);

	return VM_FAULT_LOCKED;
out_unlock:
	unlock_page(page);
	return VM_FAULT_NOPAGE;
}