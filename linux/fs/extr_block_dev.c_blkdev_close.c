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
struct file {int /*<<< orphan*/  f_mode; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct block_device* I_BDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_file_inode (struct file*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkdev_close(struct inode * inode, struct file * filp)
{
	struct block_device *bdev = I_BDEV(bdev_file_inode(filp));
	blkdev_put(bdev, filp->f_mode);
	return 0;
}