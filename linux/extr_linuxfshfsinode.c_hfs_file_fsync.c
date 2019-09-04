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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct inode {struct super_block* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  mdb_work; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* HFS_SB (struct super_block*) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int sync_blockdev (int /*<<< orphan*/ ) ; 
 int write_inode_now (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfs_file_fsync(struct file *filp, loff_t start, loff_t end,
			  int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	struct super_block * sb;
	int ret, err;

	ret = file_write_and_wait_range(filp, start, end);
	if (ret)
		return ret;
	inode_lock(inode);

	/* sync the inode to buffers */
	ret = write_inode_now(inode, 0);

	/* sync the superblock to buffers */
	sb = inode->i_sb;
	flush_delayed_work(&HFS_SB(sb)->mdb_work);
	/* .. finally sync the buffers to disk */
	err = sync_blockdev(sb->s_bdev);
	if (!ret)
		ret = err;
	inode_unlock(inode);
	return ret;
}