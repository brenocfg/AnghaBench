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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  ino; } ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;

/* Variables and functions */
 int DATA ; 
 int NODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int,int,int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  set_de_type (struct f2fs_dir_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void f2fs_set_link(struct inode *dir, struct f2fs_dir_entry *de,
		struct page *page, struct inode *inode)
{
	enum page_type type = f2fs_has_inline_dentry(dir) ? NODE : DATA;
	lock_page(page);
	f2fs_wait_on_page_writeback(page, type, true, true);
	de->ino = cpu_to_le32(inode->i_ino);
	set_de_type(de, inode->i_mode);
	set_page_dirty(page);

	dir->i_mtime = dir->i_ctime = current_time(dir);
	f2fs_mark_inode_dirty_sync(dir, false);
	f2fs_put_page(page, 1);
}