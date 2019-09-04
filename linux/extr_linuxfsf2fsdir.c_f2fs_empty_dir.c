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
struct inode {int dummy; } ;
struct f2fs_dentry_block {int /*<<< orphan*/  dentry_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned int NR_DENTRY_IN_BLOCK ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 unsigned long dir_blocks (struct inode*) ; 
 int f2fs_empty_inline_dir (struct inode*) ; 
 struct page* f2fs_get_lock_data_page (struct inode*,unsigned long,int) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int find_next_bit_le (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct f2fs_dentry_block* page_address (struct page*) ; 

bool f2fs_empty_dir(struct inode *dir)
{
	unsigned long bidx;
	struct page *dentry_page;
	unsigned int bit_pos;
	struct f2fs_dentry_block *dentry_blk;
	unsigned long nblock = dir_blocks(dir);

	if (f2fs_has_inline_dentry(dir))
		return f2fs_empty_inline_dir(dir);

	for (bidx = 0; bidx < nblock; bidx++) {
		dentry_page = f2fs_get_lock_data_page(dir, bidx, false);
		if (IS_ERR(dentry_page)) {
			if (PTR_ERR(dentry_page) == -ENOENT)
				continue;
			else
				return false;
		}

		dentry_blk = page_address(dentry_page);
		if (bidx == 0)
			bit_pos = 2;
		else
			bit_pos = 0;
		bit_pos = find_next_bit_le(&dentry_blk->dentry_bitmap,
						NR_DENTRY_IN_BLOCK,
						bit_pos);

		f2fs_put_page(dentry_page, 1);

		if (bit_pos < NR_DENTRY_IN_BLOCK)
			return false;
	}
	return true;
}