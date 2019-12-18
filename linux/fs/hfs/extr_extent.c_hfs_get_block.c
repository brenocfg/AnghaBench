#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {scalar_t__ fs_blocks; int alloc_blocks; int first_blocks; int cached_start; int /*<<< orphan*/  phys_size; int /*<<< orphan*/  extents_lock; int /*<<< orphan*/  cached_extents; int /*<<< orphan*/  first_extents; } ;
struct TYPE_3__ {int fs_div; scalar_t__ fs_start; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_2__* HFS_I (struct inode*) ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int hfs_ext_find_block (int /*<<< orphan*/ ,int) ; 
 int hfs_ext_read_extent (struct inode*,int) ; 
 int hfs_extend_file (struct inode*) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

int hfs_get_block(struct inode *inode, sector_t block,
		  struct buffer_head *bh_result, int create)
{
	struct super_block *sb;
	u16 dblock, ablock;
	int res;

	sb = inode->i_sb;
	/* Convert inode block to disk allocation block */
	ablock = (u32)block / HFS_SB(sb)->fs_div;

	if (block >= HFS_I(inode)->fs_blocks) {
		if (!create)
			return 0;
		if (block > HFS_I(inode)->fs_blocks)
			return -EIO;
		if (ablock >= HFS_I(inode)->alloc_blocks) {
			res = hfs_extend_file(inode);
			if (res)
				return res;
		}
	} else
		create = 0;

	if (ablock < HFS_I(inode)->first_blocks) {
		dblock = hfs_ext_find_block(HFS_I(inode)->first_extents, ablock);
		goto done;
	}

	mutex_lock(&HFS_I(inode)->extents_lock);
	res = hfs_ext_read_extent(inode, ablock);
	if (!res)
		dblock = hfs_ext_find_block(HFS_I(inode)->cached_extents,
					    ablock - HFS_I(inode)->cached_start);
	else {
		mutex_unlock(&HFS_I(inode)->extents_lock);
		return -EIO;
	}
	mutex_unlock(&HFS_I(inode)->extents_lock);

done:
	map_bh(bh_result, sb, HFS_SB(sb)->fs_start +
	       dblock * HFS_SB(sb)->fs_div +
	       (u32)block % HFS_SB(sb)->fs_div);

	if (create) {
		set_buffer_new(bh_result);
		HFS_I(inode)->phys_size += sb->s_blocksize;
		HFS_I(inode)->fs_blocks++;
		inode_add_bytes(inode, sb->s_blocksize);
		mark_inode_dirty(inode);
	}
	return 0;
}