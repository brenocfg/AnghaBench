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
typedef  int /*<<< orphan*/  u64 ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_writepage_fixup {int /*<<< orphan*/  work; struct page* page; } ;
struct btrfs_fs_info {int /*<<< orphan*/  fixup_workers; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ PageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 scalar_t__ TestClearPagePrivate2 (struct page*) ; 
 int /*<<< orphan*/  btrfs_fixup_helper ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_writepage_fixup_worker ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct btrfs_writepage_fixup* kzalloc (int,int /*<<< orphan*/ ) ; 

int btrfs_writepage_cow_fixup(struct page *page, u64 start, u64 end)
{
	struct inode *inode = page->mapping->host;
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_writepage_fixup *fixup;

	/* this page is properly in the ordered list */
	if (TestClearPagePrivate2(page))
		return 0;

	if (PageChecked(page))
		return -EAGAIN;

	fixup = kzalloc(sizeof(*fixup), GFP_NOFS);
	if (!fixup)
		return -EAGAIN;

	SetPageChecked(page);
	get_page(page);
	btrfs_init_work(&fixup->work, btrfs_fixup_helper,
			btrfs_writepage_fixup_worker, NULL, NULL);
	fixup->page = page;
	btrfs_queue_work(fs_info->fixup_workers, &fixup->work);
	return -EBUSY;
}