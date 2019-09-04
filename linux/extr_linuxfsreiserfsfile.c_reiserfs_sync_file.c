#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ reiserfs_barrier_flush (TYPE_2__*) ; 
 int reiserfs_commit_for_inode (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_2__*) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_sync_file(struct file *filp, loff_t start, loff_t end,
			      int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	int err;
	int barrier_done;

	err = file_write_and_wait_range(filp, start, end);
	if (err)
		return err;

	inode_lock(inode);
	BUG_ON(!S_ISREG(inode->i_mode));
	err = sync_mapping_buffers(inode->i_mapping);
	reiserfs_write_lock(inode->i_sb);
	barrier_done = reiserfs_commit_for_inode(inode);
	reiserfs_write_unlock(inode->i_sb);
	if (barrier_done != 1 && reiserfs_barrier_flush(inode->i_sb))
		blkdev_issue_flush(inode->i_sb->s_bdev, GFP_KERNEL, NULL);
	inode_unlock(inode);
	if (barrier_done < 0)
		return barrier_done;
	return (err < 0) ? -EIO : 0;
}