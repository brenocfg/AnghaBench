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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct block_device* I_BDEV (struct inode*) ; 
 struct inode* bdev_file_inode (struct file*) ; 
 int blkdev_issue_flush (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int blkdev_fsync(struct file *filp, loff_t start, loff_t end, int datasync)
{
	struct inode *bd_inode = bdev_file_inode(filp);
	struct block_device *bdev = I_BDEV(bd_inode);
	int error;
	
	error = file_write_and_wait_range(filp, start, end);
	if (error)
		return error;

	/*
	 * There is no need to serialise calls to blkdev_issue_flush with
	 * i_mutex and doing so causes performance issues with concurrent
	 * O_SYNC writers to a block device.
	 */
	error = blkdev_issue_flush(bdev, GFP_KERNEL, NULL);
	if (error == -EOPNOTSUPP)
		error = 0;

	return error;
}