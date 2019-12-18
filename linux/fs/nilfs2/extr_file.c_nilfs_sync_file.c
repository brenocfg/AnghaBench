#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct the_nilfs {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {struct the_nilfs* s_fs_info; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int nilfs_construct_dsync_segment (TYPE_2__*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nilfs_construct_segment (TYPE_2__*) ; 
 int nilfs_flush_device (struct the_nilfs*) ; 
 scalar_t__ nilfs_inode_dirty (struct inode*) ; 

int nilfs_sync_file(struct file *file, loff_t start, loff_t end, int datasync)
{
	/*
	 * Called from fsync() system call
	 * This is the only entry point that can catch write and synch
	 * timing for both data blocks and intermediate blocks.
	 *
	 * This function should be implemented when the writeback function
	 * will be implemented.
	 */
	struct the_nilfs *nilfs;
	struct inode *inode = file->f_mapping->host;
	int err = 0;

	if (nilfs_inode_dirty(inode)) {
		if (datasync)
			err = nilfs_construct_dsync_segment(inode->i_sb, inode,
							    start, end);
		else
			err = nilfs_construct_segment(inode->i_sb);
	}

	nilfs = inode->i_sb->s_fs_info;
	if (!err)
		err = nilfs_flush_device(nilfs);

	return err;
}