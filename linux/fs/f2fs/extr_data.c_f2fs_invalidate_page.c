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
struct page {TYPE_1__* mapping; } ;
struct inode {scalar_t__ i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_META ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ F2FS_META_INO (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_NODE_INO (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_ROOT_INO (struct f2fs_sb_info*) ; 
 scalar_t__ IS_ATOMIC_WRITTEN_PAGE (struct page*) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageDirty (struct page*) ; 
 int /*<<< orphan*/  clear_cold_data (struct page*) ; 
 int /*<<< orphan*/  dec_page_count (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_clear_page_private (struct page*) ; 
 void f2fs_drop_inmem_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_dec_dirty_pages (struct inode*) ; 

void f2fs_invalidate_page(struct page *page, unsigned int offset,
							unsigned int length)
{
	struct inode *inode = page->mapping->host;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (inode->i_ino >= F2FS_ROOT_INO(sbi) &&
		(offset % PAGE_SIZE || length != PAGE_SIZE))
		return;

	if (PageDirty(page)) {
		if (inode->i_ino == F2FS_META_INO(sbi)) {
			dec_page_count(sbi, F2FS_DIRTY_META);
		} else if (inode->i_ino == F2FS_NODE_INO(sbi)) {
			dec_page_count(sbi, F2FS_DIRTY_NODES);
		} else {
			inode_dec_dirty_pages(inode);
			f2fs_remove_dirty_inode(inode);
		}
	}

	clear_cold_data(page);

	if (IS_ATOMIC_WRITTEN_PAGE(page))
		return f2fs_drop_inmem_page(inode, page);

	f2fs_clear_page_private(page);
}