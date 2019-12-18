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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  name_len; } ;
struct f2fs_dentry_ptr {int /*<<< orphan*/  bitmap; struct f2fs_dir_entry* dentry; } ;

/* Variables and functions */
 int GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  __clear_bit_le (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_nlink (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  make_dentry_ptr_inline (struct inode*,struct f2fs_dentry_ptr*,void*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void f2fs_delete_inline_entry(struct f2fs_dir_entry *dentry, struct page *page,
					struct inode *dir, struct inode *inode)
{
	struct f2fs_dentry_ptr d;
	void *inline_dentry;
	int slots = GET_DENTRY_SLOTS(le16_to_cpu(dentry->name_len));
	unsigned int bit_pos;
	int i;

	lock_page(page);
	f2fs_wait_on_page_writeback(page, NODE, true, true);

	inline_dentry = inline_data_addr(dir, page);
	make_dentry_ptr_inline(dir, &d, inline_dentry);

	bit_pos = dentry - d.dentry;
	for (i = 0; i < slots; i++)
		__clear_bit_le(bit_pos + i, d.bitmap);

	set_page_dirty(page);
	f2fs_put_page(page, 1);

	dir->i_ctime = dir->i_mtime = current_time(dir);
	f2fs_mark_inode_dirty_sync(dir, false);

	if (inode)
		f2fs_drop_nlink(dir, inode);
}