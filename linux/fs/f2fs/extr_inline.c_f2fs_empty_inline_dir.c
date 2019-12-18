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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_dentry_ptr {unsigned int max; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int find_next_bit_le (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  make_dentry_ptr_inline (struct inode*,struct f2fs_dentry_ptr*,void*) ; 

bool f2fs_empty_inline_dir(struct inode *dir)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);
	struct page *ipage;
	unsigned int bit_pos = 2;
	void *inline_dentry;
	struct f2fs_dentry_ptr d;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	if (IS_ERR(ipage))
		return false;

	inline_dentry = inline_data_addr(dir, ipage);
	make_dentry_ptr_inline(dir, &d, inline_dentry);

	bit_pos = find_next_bit_le(d.bitmap, d.max, bit_pos);

	f2fs_put_page(ipage, 1);

	if (bit_pos < d.max)
		return false;

	return true;
}