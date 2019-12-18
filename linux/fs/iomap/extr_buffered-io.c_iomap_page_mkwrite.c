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
struct page {scalar_t__ mapping; int index; } ;
struct iomap_ops {int dummy; } ;
struct inode {scalar_t__ i_mapping; } ;
typedef  unsigned long ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 unsigned long EFAULT ; 
 int IOMAP_FAULT ; 
 int IOMAP_WRITE ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  VM_FAULT_LOCKED ; 
 int /*<<< orphan*/  block_page_mkwrite_return (unsigned long) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 unsigned long iomap_apply (struct inode*,int,unsigned long,int,struct iomap_ops const*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_page_mkwrite_actor ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 unsigned long offset_in_page (int) ; 
 int page_offset (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

vm_fault_t iomap_page_mkwrite(struct vm_fault *vmf, const struct iomap_ops *ops)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);
	unsigned long length;
	loff_t offset, size;
	ssize_t ret;

	lock_page(page);
	size = i_size_read(inode);
	if ((page->mapping != inode->i_mapping) ||
	    (page_offset(page) > size)) {
		/* We overload EFAULT to mean page got truncated */
		ret = -EFAULT;
		goto out_unlock;
	}

	/* page is wholly or partially inside EOF */
	if (((page->index + 1) << PAGE_SHIFT) > size)
		length = offset_in_page(size);
	else
		length = PAGE_SIZE;

	offset = page_offset(page);
	while (length > 0) {
		ret = iomap_apply(inode, offset, length,
				IOMAP_WRITE | IOMAP_FAULT, ops, page,
				iomap_page_mkwrite_actor);
		if (unlikely(ret <= 0))
			goto out_unlock;
		offset += ret;
		length -= ret;
	}

	wait_for_stable_page(page);
	return VM_FAULT_LOCKED;
out_unlock:
	unlock_page(page);
	return block_page_mkwrite_return(ret);
}