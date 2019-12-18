#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_7__ {TYPE_1__* io_end; } ;
struct ext4_map_blocks {scalar_t__ m_len; scalar_t__ m_lblk; } ;
struct mpage_da_data {scalar_t__ first_page; TYPE_2__ io_submit; struct ext4_map_blocks map; struct inode* inode; } ;
struct inode {scalar_t__ i_blkbits; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_9__ {scalar_t__ i_disksize; int /*<<< orphan*/  i_data_sem; } ;
struct TYPE_8__ {int s_mount_flags; } ;
struct TYPE_6__ {scalar_t__ offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 TYPE_5__* EXT4_I (struct inode*) ; 
 int EXT4_MF_FS_ABORTED ; 
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_count_free_clusters (struct super_block*) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_forced_shutdown (TYPE_3__*) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ext4_print_free_blocks (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int mpage_map_and_submit_buffers (struct mpage_da_data*) ; 
 int mpage_map_one_extent (int /*<<< orphan*/ *,struct mpage_da_data*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpage_map_and_submit_extent(handle_t *handle,
				       struct mpage_da_data *mpd,
				       bool *give_up_on_write)
{
	struct inode *inode = mpd->inode;
	struct ext4_map_blocks *map = &mpd->map;
	int err;
	loff_t disksize;
	int progress = 0;

	mpd->io_submit.io_end->offset =
				((loff_t)map->m_lblk) << inode->i_blkbits;
	do {
		err = mpage_map_one_extent(handle, mpd);
		if (err < 0) {
			struct super_block *sb = inode->i_sb;

			if (ext4_forced_shutdown(EXT4_SB(sb)) ||
			    EXT4_SB(sb)->s_mount_flags & EXT4_MF_FS_ABORTED)
				goto invalidate_dirty_pages;
			/*
			 * Let the uper layers retry transient errors.
			 * In the case of ENOSPC, if ext4_count_free_blocks()
			 * is non-zero, a commit should free up blocks.
			 */
			if ((err == -ENOMEM) ||
			    (err == -ENOSPC && ext4_count_free_clusters(sb))) {
				if (progress)
					goto update_disksize;
				return err;
			}
			ext4_msg(sb, KERN_CRIT,
				 "Delayed block allocation failed for "
				 "inode %lu at logical offset %llu with"
				 " max blocks %u with error %d",
				 inode->i_ino,
				 (unsigned long long)map->m_lblk,
				 (unsigned)map->m_len, -err);
			ext4_msg(sb, KERN_CRIT,
				 "This should not happen!! Data will "
				 "be lost\n");
			if (err == -ENOSPC)
				ext4_print_free_blocks(inode);
		invalidate_dirty_pages:
			*give_up_on_write = true;
			return err;
		}
		progress = 1;
		/*
		 * Update buffer state, submit mapped pages, and get us new
		 * extent to map
		 */
		err = mpage_map_and_submit_buffers(mpd);
		if (err < 0)
			goto update_disksize;
	} while (map->m_len);

update_disksize:
	/*
	 * Update on-disk size after IO is submitted.  Races with
	 * truncate are avoided by checking i_size under i_data_sem.
	 */
	disksize = ((loff_t)mpd->first_page) << PAGE_SHIFT;
	if (disksize > EXT4_I(inode)->i_disksize) {
		int err2;
		loff_t i_size;

		down_write(&EXT4_I(inode)->i_data_sem);
		i_size = i_size_read(inode);
		if (disksize > i_size)
			disksize = i_size;
		if (disksize > EXT4_I(inode)->i_disksize)
			EXT4_I(inode)->i_disksize = disksize;
		up_write(&EXT4_I(inode)->i_data_sem);
		err2 = ext4_mark_inode_dirty(handle, inode);
		if (err2)
			ext4_error(inode->i_sb,
				   "Failed to mark inode %lu dirty",
				   inode->i_ino);
		if (!err)
			err = err2;
	}
	return err;
}