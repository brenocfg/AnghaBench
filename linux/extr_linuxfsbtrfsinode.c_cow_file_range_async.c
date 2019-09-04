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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delalloc_workers; int /*<<< orphan*/  async_delalloc_pages; } ;
struct async_cow {unsigned int write_flags; int /*<<< orphan*/  work; int /*<<< orphan*/  extents; scalar_t__ end; scalar_t__ start; struct page* locked_page; struct btrfs_root* root; int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NOCOMPRESS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXTENT_LOCKED ; 
 int /*<<< orphan*/  FORCE_COMPRESS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SZ_512K ; 
 int /*<<< orphan*/  async_cow_free ; 
 int /*<<< orphan*/  async_cow_start ; 
 int /*<<< orphan*/  async_cow_submit ; 
 int /*<<< orphan*/  atomic_add (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_delalloc_helper ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_bit (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 struct async_cow* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cow_file_range_async(struct inode *inode, struct page *locked_page,
				u64 start, u64 end, int *page_started,
				unsigned long *nr_written,
				unsigned int write_flags)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct async_cow *async_cow;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	unsigned long nr_pages;
	u64 cur_end;

	clear_extent_bit(&BTRFS_I(inode)->io_tree, start, end, EXTENT_LOCKED,
			 1, 0, NULL);
	while (start < end) {
		async_cow = kmalloc(sizeof(*async_cow), GFP_NOFS);
		BUG_ON(!async_cow); /* -ENOMEM */
		async_cow->inode = igrab(inode);
		async_cow->root = root;
		async_cow->locked_page = locked_page;
		async_cow->start = start;
		async_cow->write_flags = write_flags;

		if (BTRFS_I(inode)->flags & BTRFS_INODE_NOCOMPRESS &&
		    !btrfs_test_opt(fs_info, FORCE_COMPRESS))
			cur_end = end;
		else
			cur_end = min(end, start + SZ_512K - 1);

		async_cow->end = cur_end;
		INIT_LIST_HEAD(&async_cow->extents);

		btrfs_init_work(&async_cow->work,
				btrfs_delalloc_helper,
				async_cow_start, async_cow_submit,
				async_cow_free);

		nr_pages = (cur_end - start + PAGE_SIZE) >>
			PAGE_SHIFT;
		atomic_add(nr_pages, &fs_info->async_delalloc_pages);

		btrfs_queue_work(fs_info->delalloc_workers, &async_cow->work);

		*nr_written += nr_pages;
		start = cur_end + 1;
	}
	*page_started = 1;
	return 0;
}