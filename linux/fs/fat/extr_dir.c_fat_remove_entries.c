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
struct super_block {int dummy; } ;
struct msdos_dir_entry {int /*<<< orphan*/ * name; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {int nr_slots; int /*<<< orphan*/  slot_off; struct buffer_head* bh; struct msdos_dir_entry* de; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED_FLAG ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int S_ATIME ; 
 int S_MTIME ; 
 int __fat_remove_entries (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fat_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fat_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  fat_truncate_time (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 

int fat_remove_entries(struct inode *dir, struct fat_slot_info *sinfo)
{
	struct super_block *sb = dir->i_sb;
	struct msdos_dir_entry *de;
	struct buffer_head *bh;
	int err = 0, nr_slots;

	/*
	 * First stage: Remove the shortname. By this, the directory
	 * entry is removed.
	 */
	nr_slots = sinfo->nr_slots;
	de = sinfo->de;
	sinfo->de = NULL;
	bh = sinfo->bh;
	sinfo->bh = NULL;
	while (nr_slots && de >= (struct msdos_dir_entry *)bh->b_data) {
		de->name[0] = DELETED_FLAG;
		de--;
		nr_slots--;
	}
	mark_buffer_dirty_inode(bh, dir);
	if (IS_DIRSYNC(dir))
		err = sync_dirty_buffer(bh);
	brelse(bh);
	if (err)
		return err;
	inode_inc_iversion(dir);

	if (nr_slots) {
		/*
		 * Second stage: remove the remaining longname slots.
		 * (This directory entry is already removed, and so return
		 * the success)
		 */
		err = __fat_remove_entries(dir, sinfo->slot_off, nr_slots);
		if (err) {
			fat_msg(sb, KERN_WARNING,
			       "Couldn't remove the long name slots");
		}
	}

	fat_truncate_time(dir, NULL, S_ATIME|S_MTIME);
	if (IS_DIRSYNC(dir))
		(void)fat_sync_inode(dir);
	else
		mark_inode_dirty(dir);

	return 0;
}