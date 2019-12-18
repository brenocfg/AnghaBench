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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int FGP_LOCK ; 
 int FGP_NOWAIT ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 struct page* f2fs_pagecache_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_remove_dirty_inode (struct inode*) ; 
 int f2fs_write_inline_data (struct inode*,struct page*) ; 
 struct inode* ilookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_dec_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static void flush_inline_data(struct f2fs_sb_info *sbi, nid_t ino)
{
	struct inode *inode;
	struct page *page;
	int ret;

	/* should flush inline_data before evict_inode */
	inode = ilookup(sbi->sb, ino);
	if (!inode)
		return;

	page = f2fs_pagecache_get_page(inode->i_mapping, 0,
					FGP_LOCK|FGP_NOWAIT, 0);
	if (!page)
		goto iput_out;

	if (!PageUptodate(page))
		goto page_out;

	if (!PageDirty(page))
		goto page_out;

	if (!clear_page_dirty_for_io(page))
		goto page_out;

	ret = f2fs_write_inline_data(inode, page);
	inode_dec_dirty_pages(inode);
	f2fs_remove_dirty_inode(inode);
	if (ret)
		set_page_dirty(page);
page_out:
	f2fs_put_page(page, 1);
iput_out:
	iput(inode);
}