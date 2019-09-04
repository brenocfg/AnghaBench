#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; int /*<<< orphan*/  f_mode; int /*<<< orphan*/  f_mapping; int /*<<< orphan*/  f_wb_err; } ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FMODE_EXCL ; 
 int /*<<< orphan*/  FMODE_NDELAY ; 
 int /*<<< orphan*/  FMODE_NOWAIT ; 
 int /*<<< orphan*/  FMODE_WRITE_IOCTL ; 
 int O_ACCMODE ; 
 int O_EXCL ; 
 int O_LARGEFILE ; 
 int O_NDELAY ; 
 struct block_device* bd_acquire (struct inode*) ; 
 int blkdev_get (struct block_device*,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  filemap_sample_wb_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blkdev_open(struct inode * inode, struct file * filp)
{
	struct block_device *bdev;

	/*
	 * Preserve backwards compatibility and allow large file access
	 * even if userspace doesn't ask for it explicitly. Some mkfs
	 * binary needs it. We might want to drop this workaround
	 * during an unstable branch.
	 */
	filp->f_flags |= O_LARGEFILE;

	filp->f_mode |= FMODE_NOWAIT;

	if (filp->f_flags & O_NDELAY)
		filp->f_mode |= FMODE_NDELAY;
	if (filp->f_flags & O_EXCL)
		filp->f_mode |= FMODE_EXCL;
	if ((filp->f_flags & O_ACCMODE) == 3)
		filp->f_mode |= FMODE_WRITE_IOCTL;

	bdev = bd_acquire(inode);
	if (bdev == NULL)
		return -ENOMEM;

	filp->f_mapping = bdev->bd_inode->i_mapping;
	filp->f_wb_err = filemap_sample_wb_err(filp->f_mapping);

	return blkdev_get(bdev, filp->f_mode, filp);
}