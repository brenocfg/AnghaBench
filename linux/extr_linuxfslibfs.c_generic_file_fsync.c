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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __generic_file_fsync (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int generic_file_fsync(struct file *file, loff_t start, loff_t end,
		       int datasync)
{
	struct inode *inode = file->f_mapping->host;
	int err;

	err = __generic_file_fsync(file, start, end, datasync);
	if (err)
		return err;
	return blkdev_issue_flush(inode->i_sb->s_bdev, GFP_KERNEL, NULL);
}