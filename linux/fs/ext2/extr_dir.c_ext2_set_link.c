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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct ext2_dir_entry_2 {int /*<<< orphan*/  inode; int /*<<< orphan*/  rec_len; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXT2_BTREE_FL ; 
 TYPE_1__* EXT2_I (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int ext2_commit_chunk (struct page*,int,unsigned int) ; 
 int ext2_prepare_chunk (struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  ext2_put_page (struct page*) ; 
 unsigned int ext2_rec_len_from_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_set_de_type (struct ext2_dir_entry_2*,struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 

void ext2_set_link(struct inode *dir, struct ext2_dir_entry_2 *de,
		   struct page *page, struct inode *inode, int update_times)
{
	loff_t pos = page_offset(page) +
			(char *) de - (char *) page_address(page);
	unsigned len = ext2_rec_len_from_disk(de->rec_len);
	int err;

	lock_page(page);
	err = ext2_prepare_chunk(page, pos, len);
	BUG_ON(err);
	de->inode = cpu_to_le32(inode->i_ino);
	ext2_set_de_type(de, inode);
	err = ext2_commit_chunk(page, pos, len);
	ext2_put_page(page);
	if (update_times)
		dir->i_mtime = dir->i_ctime = current_time(dir);
	EXT2_I(dir)->i_flags &= ~EXT2_BTREE_FL;
	mark_inode_dirty(dir);
}