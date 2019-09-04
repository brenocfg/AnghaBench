#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {scalar_t__ s_maxbytes; } ;
struct TYPE_5__ {scalar_t__ s_bitmap_maxbytes; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 TYPE_2__* EXT4_SB (TYPE_3__*) ; 
#define  SEEK_DATA 129 
#define  SEEK_HOLE 128 
 int /*<<< orphan*/  ext4_iomap_ops ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ generic_file_llseek_size (struct file*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 scalar_t__ iomap_seek_data (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ iomap_seek_hole (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_setpos (struct file*,scalar_t__,scalar_t__) ; 

loff_t ext4_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	loff_t maxbytes;

	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		maxbytes = EXT4_SB(inode->i_sb)->s_bitmap_maxbytes;
	else
		maxbytes = inode->i_sb->s_maxbytes;

	switch (whence) {
	default:
		return generic_file_llseek_size(file, offset, whence,
						maxbytes, i_size_read(inode));
	case SEEK_HOLE:
		inode_lock_shared(inode);
		offset = iomap_seek_hole(inode, offset, &ext4_iomap_ops);
		inode_unlock_shared(inode);
		break;
	case SEEK_DATA:
		inode_lock_shared(inode);
		offset = iomap_seek_data(inode, offset, &ext4_iomap_ops);
		inode_unlock_shared(inode);
		break;
	}

	if (offset < 0)
		return offset;
	return vfs_setpos(file, offset, maxbytes);
}