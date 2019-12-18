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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {TYPE_1__* vma; struct page* page; } ;
struct page {scalar_t__ mapping; scalar_t__ index; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_sb; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {int node_changed; int /*<<< orphan*/  data_blkaddr; } ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_mmap_sem; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_MAPPED_IO ; 
 int /*<<< orphan*/  DATA ; 
 int EFAULT ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 int /*<<< orphan*/  F2FS_GET_BLOCK_PRE_AIO ; 
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  REQ_TIME ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  __do_map_lock (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  block_page_mkwrite_return (int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_cp_error (struct f2fs_sb_info*) ; 
 int f2fs_get_block (struct dnode_of_data*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_block_writeback (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_update_time (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  trace_f2fs_vm_page_mkwrite (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t f2fs_vm_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct dnode_of_data dn = { .node_changed = false };
	int err;

	if (unlikely(f2fs_cp_error(sbi))) {
		err = -EIO;
		goto err;
	}

	if (!f2fs_is_checkpoint_ready(sbi)) {
		err = -ENOSPC;
		goto err;
	}

	sb_start_pagefault(inode->i_sb);

	f2fs_bug_on(sbi, f2fs_has_inline_data(inode));

	file_update_time(vmf->vma->vm_file);
	down_read(&F2FS_I(inode)->i_mmap_sem);
	lock_page(page);
	if (unlikely(page->mapping != inode->i_mapping ||
			page_offset(page) > i_size_read(inode) ||
			!PageUptodate(page))) {
		unlock_page(page);
		err = -EFAULT;
		goto out_sem;
	}

	/* block allocation */
	__do_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, true);
	set_new_dnode(&dn, inode, NULL, NULL, 0);
	err = f2fs_get_block(&dn, page->index);
	f2fs_put_dnode(&dn);
	__do_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, false);
	if (err) {
		unlock_page(page);
		goto out_sem;
	}

	/* fill the page */
	f2fs_wait_on_page_writeback(page, DATA, false, true);

	/* wait for GCed page writeback via META_MAPPING */
	f2fs_wait_on_block_writeback(inode, dn.data_blkaddr);

	/*
	 * check to see if the page is mapped already (no holes)
	 */
	if (PageMappedToDisk(page))
		goto out_sem;

	/* page is wholly or partially inside EOF */
	if (((loff_t)(page->index + 1) << PAGE_SHIFT) >
						i_size_read(inode)) {
		loff_t offset;

		offset = i_size_read(inode) & ~PAGE_MASK;
		zero_user_segment(page, offset, PAGE_SIZE);
	}
	set_page_dirty(page);
	if (!PageUptodate(page))
		SetPageUptodate(page);

	f2fs_update_iostat(sbi, APP_MAPPED_IO, F2FS_BLKSIZE);
	f2fs_update_time(sbi, REQ_TIME);

	trace_f2fs_vm_page_mkwrite(page, DATA);
out_sem:
	up_read(&F2FS_I(inode)->i_mmap_sem);

	f2fs_balance_fs(sbi, dn.node_changed);

	sb_end_pagefault(inode->i_sb);
err:
	return block_page_mkwrite_return(err);
}