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
struct vm_fault {TYPE_1__* vma; struct page* page; } ;
struct page {scalar_t__ mapping; } ;
struct orangefs_write_range {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; void* len; void* pos; } ;
struct orangefs_inode_s {unsigned long bitlock; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 void* PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int VM_FAULT_LOCKED ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_RETRY ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_update_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orangefs_write_range* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ orangefs_launder_page (struct page*) ; 
 void* page_offset (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 
 scalar_t__ wait_on_bit (unsigned long*,int,int /*<<< orphan*/ ) ; 

vm_fault_t orangefs_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	unsigned long *bitlock = &orangefs_inode->bitlock;
	vm_fault_t ret;
	struct orangefs_write_range *wr;

	sb_start_pagefault(inode->i_sb);

	if (wait_on_bit(bitlock, 1, TASK_KILLABLE)) {
		ret = VM_FAULT_RETRY;
		goto out;
	}

	lock_page(page);
	if (PageDirty(page) && !PagePrivate(page)) {
		/*
		 * Should be impossible.  If it happens, launder the page
		 * since we don't know what's dirty.  This will WARN in
		 * orangefs_writepage_locked.
		 */
		if (orangefs_launder_page(page)) {
			ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
			goto out;
		}
	}
	if (PagePrivate(page)) {
		wr = (struct orangefs_write_range *)page_private(page);
		if (uid_eq(wr->uid, current_fsuid()) &&
		    gid_eq(wr->gid, current_fsgid())) {
			wr->pos = page_offset(page);
			wr->len = PAGE_SIZE;
			goto okay;
		} else {
			if (orangefs_launder_page(page)) {
				ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
				goto out;
			}
		}
	}
	wr = kmalloc(sizeof *wr, GFP_KERNEL);
	if (!wr) {
		ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
		goto out;
	}
	wr->pos = page_offset(page);
	wr->len = PAGE_SIZE;
	wr->uid = current_fsuid();
	wr->gid = current_fsgid();
	SetPagePrivate(page);
	set_page_private(page, (unsigned long)wr);
	get_page(page);
okay:

	file_update_time(vmf->vma->vm_file);
	if (page->mapping != inode->i_mapping) {
		unlock_page(page);
		ret = VM_FAULT_LOCKED|VM_FAULT_NOPAGE;
		goto out;
	}

	/*
	 * We mark the page dirty already here so that when freeze is in
	 * progress, we are guaranteed that writeback during freezing will
	 * see the dirty page and writeprotect it again.
	 */
	set_page_dirty(page);
	wait_for_stable_page(page);
	ret = VM_FAULT_LOCKED;
out:
	sb_end_pagefault(inode->i_sb);
	return ret;
}