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
struct super_block {unsigned int s_blocksize; } ;
struct inode {unsigned int i_size; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  rec_len; int /*<<< orphan*/  inode; int /*<<< orphan*/  name; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRENT_HTREE ; 
 int /*<<< orphan*/  EITHER ; 
 unsigned int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 unsigned int EXT4_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int empty_inline_dir (struct inode*,int*) ; 
 scalar_t__ ext4_check_dir_entry (struct inode*,int /*<<< orphan*/ *,struct ext4_dir_entry_2*,struct buffer_head*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,unsigned int) ; 
 struct buffer_head* ext4_read_dirblock (struct inode*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int ext4_rec_len_from_disk (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_warning_inode (struct inode*,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

bool ext4_empty_dir(struct inode *inode)
{
	unsigned int offset;
	struct buffer_head *bh;
	struct ext4_dir_entry_2 *de, *de1;
	struct super_block *sb;

	if (ext4_has_inline_data(inode)) {
		int has_inline_data = 1;
		int ret;

		ret = empty_inline_dir(inode, &has_inline_data);
		if (has_inline_data)
			return ret;
	}

	sb = inode->i_sb;
	if (inode->i_size < EXT4_DIR_REC_LEN(1) + EXT4_DIR_REC_LEN(2)) {
		EXT4_ERROR_INODE(inode, "invalid size");
		return true;
	}
	/* The first directory block must not be a hole,
	 * so treat it as DIRENT_HTREE
	 */
	bh = ext4_read_dirblock(inode, 0, DIRENT_HTREE);
	if (IS_ERR(bh))
		return true;

	de = (struct ext4_dir_entry_2 *) bh->b_data;
	de1 = ext4_next_entry(de, sb->s_blocksize);
	if (le32_to_cpu(de->inode) != inode->i_ino ||
			le32_to_cpu(de1->inode) == 0 ||
			strcmp(".", de->name) || strcmp("..", de1->name)) {
		ext4_warning_inode(inode, "directory missing '.' and/or '..'");
		brelse(bh);
		return true;
	}
	offset = ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize) +
		 ext4_rec_len_from_disk(de1->rec_len, sb->s_blocksize);
	de = ext4_next_entry(de1, sb->s_blocksize);
	while (offset < inode->i_size) {
		if ((void *) de >= (void *) (bh->b_data+sb->s_blocksize)) {
			unsigned int lblock;
			brelse(bh);
			lblock = offset >> EXT4_BLOCK_SIZE_BITS(sb);
			bh = ext4_read_dirblock(inode, lblock, EITHER);
			if (bh == NULL) {
				offset += sb->s_blocksize;
				continue;
			}
			if (IS_ERR(bh))
				return true;
			de = (struct ext4_dir_entry_2 *) bh->b_data;
		}
		if (ext4_check_dir_entry(inode, NULL, de, bh,
					 bh->b_data, bh->b_size, offset)) {
			de = (struct ext4_dir_entry_2 *)(bh->b_data +
							 sb->s_blocksize);
			offset = (offset | (sb->s_blocksize - 1)) + 1;
			continue;
		}
		if (le32_to_cpu(de->inode)) {
			brelse(bh);
			return false;
		}
		offset += ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize);
		de = ext4_next_entry(de, sb->s_blocksize);
	}
	brelse(bh);
	return true;
}