#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct page {TYPE_1__* mapping; } ;
struct inode {int i_state; } ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_ordered_inode_tree {int /*<<< orphan*/  lock; } ;
struct btrfs_ordered_extent {scalar_t__ file_offset; scalar_t__ len; scalar_t__ truncated_len; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {struct btrfs_ordered_inode_tree ordered_tree; struct extent_io_tree io_tree; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_ORDERED_TRUNCATED ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int EXTENT_DEFRAG ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DELALLOC_NEW ; 
 int EXTENT_DO_ACCOUNTING ; 
 int EXTENT_LOCKED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int I_FREEING ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ TestClearPagePrivate2 (struct page*) ; 
 int /*<<< orphan*/  __btrfs_releasepage (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_dec_test_ordered_pending (struct inode*,struct btrfs_ordered_extent**,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_finish_ordered_io (struct btrfs_ordered_extent*) ; 
 struct btrfs_ordered_extent* btrfs_lookup_ordered_range (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_data (struct inode*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_releasepage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_bit (struct extent_io_tree*,scalar_t__,scalar_t__,int,int,int,struct extent_state**) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static void btrfs_invalidatepage(struct page *page, unsigned int offset,
				 unsigned int length)
{
	struct inode *inode = page->mapping->host;
	struct extent_io_tree *tree;
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cached_state = NULL;
	u64 page_start = page_offset(page);
	u64 page_end = page_start + PAGE_SIZE - 1;
	u64 start;
	u64 end;
	int inode_evicting = inode->i_state & I_FREEING;

	/*
	 * we have the page locked, so new writeback can't start,
	 * and the dirty bit won't be cleared while we are here.
	 *
	 * Wait for IO on this page so that we can safely clear
	 * the PagePrivate2 bit and do ordered accounting
	 */
	wait_on_page_writeback(page);

	tree = &BTRFS_I(inode)->io_tree;
	if (offset) {
		btrfs_releasepage(page, GFP_NOFS);
		return;
	}

	if (!inode_evicting)
		lock_extent_bits(tree, page_start, page_end, &cached_state);
again:
	start = page_start;
	ordered = btrfs_lookup_ordered_range(BTRFS_I(inode), start,
					page_end - start + 1);
	if (ordered) {
		end = min(page_end, ordered->file_offset + ordered->len - 1);
		/*
		 * IO on this page will never be started, so we need
		 * to account for any ordered extents now
		 */
		if (!inode_evicting)
			clear_extent_bit(tree, start, end,
					 EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
					 EXTENT_LOCKED | EXTENT_DO_ACCOUNTING |
					 EXTENT_DEFRAG, 1, 0, &cached_state);
		/*
		 * whoever cleared the private bit is responsible
		 * for the finish_ordered_io
		 */
		if (TestClearPagePrivate2(page)) {
			struct btrfs_ordered_inode_tree *tree;
			u64 new_len;

			tree = &BTRFS_I(inode)->ordered_tree;

			spin_lock_irq(&tree->lock);
			set_bit(BTRFS_ORDERED_TRUNCATED, &ordered->flags);
			new_len = start - ordered->file_offset;
			if (new_len < ordered->truncated_len)
				ordered->truncated_len = new_len;
			spin_unlock_irq(&tree->lock);

			if (btrfs_dec_test_ordered_pending(inode, &ordered,
							   start,
							   end - start + 1, 1))
				btrfs_finish_ordered_io(ordered);
		}
		btrfs_put_ordered_extent(ordered);
		if (!inode_evicting) {
			cached_state = NULL;
			lock_extent_bits(tree, start, end,
					 &cached_state);
		}

		start = end + 1;
		if (start < page_end)
			goto again;
	}

	/*
	 * Qgroup reserved space handler
	 * Page here will be either
	 * 1) Already written to disk
	 *    In this case, its reserved space is released from data rsv map
	 *    and will be freed by delayed_ref handler finally.
	 *    So even we call qgroup_free_data(), it won't decrease reserved
	 *    space.
	 * 2) Not written to disk
	 *    This means the reserved space should be freed here. However,
	 *    if a truncate invalidates the page (by clearing PageDirty)
	 *    and the page is accounted for while allocating extent
	 *    in btrfs_check_data_free_space() we let delayed_ref to
	 *    free the entire extent.
	 */
	if (PageDirty(page))
		btrfs_qgroup_free_data(inode, NULL, page_start, PAGE_SIZE);
	if (!inode_evicting) {
		clear_extent_bit(tree, page_start, page_end, EXTENT_LOCKED |
				 EXTENT_DELALLOC | EXTENT_DELALLOC_NEW |
				 EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG, 1, 1,
				 &cached_state);

		__btrfs_releasepage(page, GFP_NOFS);
	}

	ClearPageChecked(page);
	if (PagePrivate(page)) {
		ClearPagePrivate(page);
		set_page_private(page, 0);
		put_page(page);
	}
}