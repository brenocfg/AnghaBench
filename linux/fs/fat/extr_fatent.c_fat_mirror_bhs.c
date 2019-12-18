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
struct super_block {int s_flags; int /*<<< orphan*/  s_blocksize; } ;
struct msdos_sb_info {int fats; int fat_length; int /*<<< orphan*/  fat_inode; } ;
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_data; } ;
typedef  int sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int SB_SYNCHRONOUS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int fat_mirror_bhs(struct super_block *sb, struct buffer_head **bhs,
			  int nr_bhs)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *c_bh;
	int err, n, copy;

	err = 0;
	for (copy = 1; copy < sbi->fats; copy++) {
		sector_t backup_fat = sbi->fat_length * copy;

		for (n = 0; n < nr_bhs; n++) {
			c_bh = sb_getblk(sb, backup_fat + bhs[n]->b_blocknr);
			if (!c_bh) {
				err = -ENOMEM;
				goto error;
			}
			/* Avoid race with userspace read via bdev */
			lock_buffer(c_bh);
			memcpy(c_bh->b_data, bhs[n]->b_data, sb->s_blocksize);
			set_buffer_uptodate(c_bh);
			unlock_buffer(c_bh);
			mark_buffer_dirty_inode(c_bh, sbi->fat_inode);
			if (sb->s_flags & SB_SYNCHRONOUS)
				err = sync_dirty_buffer(c_bh);
			brelse(c_bh);
			if (err)
				goto error;
		}
	}
error:
	return err;
}