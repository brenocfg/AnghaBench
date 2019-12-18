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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_reclaim; } ;
struct super_block {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EROFS ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  nilfs_clear_dirty_page (struct page*,int) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_flush_segment (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
nilfs_mdt_write_page(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct super_block *sb;
	int err = 0;

	if (inode && sb_rdonly(inode->i_sb)) {
		/*
		 * It means that filesystem was remounted in read-only
		 * mode because of error or metadata corruption. But we
		 * have dirty pages that try to be flushed in background.
		 * So, here we simply discard this dirty page.
		 */
		nilfs_clear_dirty_page(page, false);
		unlock_page(page);
		return -EROFS;
	}

	redirty_page_for_writepage(wbc, page);
	unlock_page(page);

	if (!inode)
		return 0;

	sb = inode->i_sb;

	if (wbc->sync_mode == WB_SYNC_ALL)
		err = nilfs_construct_segment(sb);
	else if (wbc->for_reclaim)
		nilfs_flush_segment(sb, inode->i_ino);

	return err;
}