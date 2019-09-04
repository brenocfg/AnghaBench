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
struct vm_fault {struct page* page; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_file; } ;
struct page {scalar_t__ mapping; int index; } ;
struct inode {scalar_t__ i_mapping; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int EFAULT ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int __block_write_begin (struct page*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int block_commit_write (struct page*,int /*<<< orphan*/ ,unsigned long) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

int block_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf,
			 get_block_t get_block)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vma->vm_file);
	unsigned long end;
	loff_t size;
	int ret;

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
		end = size & ~PAGE_MASK;
	else
		end = PAGE_SIZE;

	ret = __block_write_begin(page, 0, end, get_block);
	if (!ret)
		ret = block_commit_write(page, 0, end);

	if (unlikely(ret < 0))
		goto out_unlock;
	set_page_dirty(page);
	wait_for_stable_page(page);
	return 0;
out_unlock:
	unlock_page(page);
	return ret;
}