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
struct super_block {scalar_t__ s_blocksize; } ;
struct msdos_dir_entry {int /*<<< orphan*/ * name; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED_FLAG ; 
 int EIO ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ fat_get_entry (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int __fat_remove_entries(struct inode *dir, loff_t pos, int nr_slots)
{
	struct super_block *sb = dir->i_sb;
	struct buffer_head *bh;
	struct msdos_dir_entry *de, *endp;
	int err = 0, orig_slots;

	while (nr_slots) {
		bh = NULL;
		if (fat_get_entry(dir, &pos, &bh, &de) < 0) {
			err = -EIO;
			break;
		}

		orig_slots = nr_slots;
		endp = (struct msdos_dir_entry *)(bh->b_data + sb->s_blocksize);
		while (nr_slots && de < endp) {
			de->name[0] = DELETED_FLAG;
			de++;
			nr_slots--;
		}
		mark_buffer_dirty_inode(bh, dir);
		if (IS_DIRSYNC(dir))
			err = sync_dirty_buffer(bh);
		brelse(bh);
		if (err)
			break;

		/* pos is *next* de's position, so this does `- sizeof(de)' */
		pos += ((orig_slots - nr_slots) * sizeof(*de)) - sizeof(*de);
	}

	return err;
}