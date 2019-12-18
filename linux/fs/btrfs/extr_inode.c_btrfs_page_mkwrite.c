#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_fault_t ;
typedef  int u64 ;
struct vm_fault {TYPE_1__* vma; struct page* page; } ;
struct page {scalar_t__ mapping; int index; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_sb; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct extent_changeset {int dummy; } ;
struct btrfs_ordered_extent {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  generation; int /*<<< orphan*/  sectorsize; } ;
typedef  int loff_t ;
struct TYPE_8__ {TYPE_2__* root; int /*<<< orphan*/  last_log_commit; int /*<<< orphan*/  last_sub_trans; int /*<<< orphan*/  last_trans; struct extent_io_tree io_tree; } ;
struct TYPE_7__ {int /*<<< orphan*/  last_log_commit; int /*<<< orphan*/  log_transid; } ;
struct TYPE_6__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int EXTENT_DEFRAG ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DO_ACCOUNTING ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ VM_FAULT_LOCKED ; 
 scalar_t__ VM_FAULT_NOPAGE ; 
 scalar_t__ VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  btrfs_delalloc_release_extents (TYPE_3__*,int) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_space (struct inode*,struct extent_changeset*,int,int,int) ; 
 int btrfs_delalloc_reserve_space (struct inode*,struct extent_changeset**,int,int) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_range (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int btrfs_set_extent_delalloc (struct inode*,int,int,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (struct inode*,struct btrfs_ordered_extent*,int) ; 
 int /*<<< orphan*/  clear_extent_bit (struct extent_io_tree*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  extent_changeset_free (struct extent_changeset*) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int file_update_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int i_size_read (struct inode*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,int,int,struct extent_state**) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 unsigned long offset_in_page (int) ; 
 int page_offset (struct page*) ; 
 int round_up (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_extent_mapped (struct page*) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,int,int,struct extent_state**) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ vmf_error (int) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

vm_fault_t btrfs_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	struct extent_changeset *data_reserved = NULL;
	char *kaddr;
	unsigned long zero_start;
	loff_t size;
	vm_fault_t ret;
	int ret2;
	int reserved = 0;
	u64 reserved_space;
	u64 page_start;
	u64 page_end;
	u64 end;

	reserved_space = PAGE_SIZE;

	sb_start_pagefault(inode->i_sb);
	page_start = page_offset(page);
	page_end = page_start + PAGE_SIZE - 1;
	end = page_end;

	/*
	 * Reserving delalloc space after obtaining the page lock can lead to
	 * deadlock. For example, if a dirty page is locked by this function
	 * and the call to btrfs_delalloc_reserve_space() ends up triggering
	 * dirty page write out, then the btrfs_writepage() function could
	 * end up waiting indefinitely to get a lock on the page currently
	 * being processed by btrfs_page_mkwrite() function.
	 */
	ret2 = btrfs_delalloc_reserve_space(inode, &data_reserved, page_start,
					   reserved_space);
	if (!ret2) {
		ret2 = file_update_time(vmf->vma->vm_file);
		reserved = 1;
	}
	if (ret2) {
		ret = vmf_error(ret2);
		if (reserved)
			goto out;
		goto out_noreserve;
	}

	ret = VM_FAULT_NOPAGE; /* make the VM retry the fault */
again:
	lock_page(page);
	size = i_size_read(inode);

	if ((page->mapping != inode->i_mapping) ||
	    (page_start >= size)) {
		/* page got truncated out from underneath us */
		goto out_unlock;
	}
	wait_on_page_writeback(page);

	lock_extent_bits(io_tree, page_start, page_end, &cached_state);
	set_page_extent_mapped(page);

	/*
	 * we can't set the delalloc bits if there are pending ordered
	 * extents.  Drop our locks and wait for them to finish
	 */
	ordered = btrfs_lookup_ordered_range(BTRFS_I(inode), page_start,
			PAGE_SIZE);
	if (ordered) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state);
		unlock_page(page);
		btrfs_start_ordered_extent(inode, ordered, 1);
		btrfs_put_ordered_extent(ordered);
		goto again;
	}

	if (page->index == ((size - 1) >> PAGE_SHIFT)) {
		reserved_space = round_up(size - page_start,
					  fs_info->sectorsize);
		if (reserved_space < PAGE_SIZE) {
			end = page_start + reserved_space - 1;
			btrfs_delalloc_release_space(inode, data_reserved,
					page_start, PAGE_SIZE - reserved_space,
					true);
		}
	}

	/*
	 * page_mkwrite gets called when the page is firstly dirtied after it's
	 * faulted in, but write(2) could also dirty a page and set delalloc
	 * bits, thus in this case for space account reason, we still need to
	 * clear any delalloc bits within this page range since we have to
	 * reserve data&meta space before lock_page() (see above comments).
	 */
	clear_extent_bit(&BTRFS_I(inode)->io_tree, page_start, end,
			  EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING |
			  EXTENT_DEFRAG, 0, 0, &cached_state);

	ret2 = btrfs_set_extent_delalloc(inode, page_start, end, 0,
					&cached_state);
	if (ret2) {
		unlock_extent_cached(io_tree, page_start, page_end,
				     &cached_state);
		ret = VM_FAULT_SIGBUS;
		goto out_unlock;
	}
	ret2 = 0;

	/* page is wholly or partially inside EOF */
	if (page_start + PAGE_SIZE > size)
		zero_start = offset_in_page(size);
	else
		zero_start = PAGE_SIZE;

	if (zero_start != PAGE_SIZE) {
		kaddr = kmap(page);
		memset(kaddr + zero_start, 0, PAGE_SIZE - zero_start);
		flush_dcache_page(page);
		kunmap(page);
	}
	ClearPageChecked(page);
	set_page_dirty(page);
	SetPageUptodate(page);

	BTRFS_I(inode)->last_trans = fs_info->generation;
	BTRFS_I(inode)->last_sub_trans = BTRFS_I(inode)->root->log_transid;
	BTRFS_I(inode)->last_log_commit = BTRFS_I(inode)->root->last_log_commit;

	unlock_extent_cached(io_tree, page_start, page_end, &cached_state);

	if (!ret2) {
		btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
		sb_end_pagefault(inode->i_sb);
		extent_changeset_free(data_reserved);
		return VM_FAULT_LOCKED;
	}

out_unlock:
	unlock_page(page);
out:
	btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
	btrfs_delalloc_release_space(inode, data_reserved, page_start,
				     reserved_space, (ret != 0));
out_noreserve:
	sb_end_pagefault(inode->i_sb);
	extent_changeset_free(data_reserved);
	return ret;
}