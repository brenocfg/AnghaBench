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
struct inode {TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int sync_blockdev (int /*<<< orphan*/ ) ; 
 int write_inode_now (struct inode*,int /*<<< orphan*/ ) ; 

int affs_file_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	int ret, err;

	err = file_write_and_wait_range(filp, start, end);
	if (err)
		return err;

	inode_lock(inode);
	ret = write_inode_now(inode, 0);
	err = sync_blockdev(inode->i_sb->s_bdev);
	if (!ret)
		ret = err;
	inode_unlock(inode);
	return ret;
}