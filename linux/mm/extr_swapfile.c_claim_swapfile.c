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
struct swap_info_struct {int /*<<< orphan*/ * bdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  old_block_size; } ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/ * s_bdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int /*<<< orphan*/  I_BDEV (struct inode*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SWP_BLKDEV ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bdgrab (int /*<<< orphan*/ ) ; 
 int blkdev_get (int /*<<< orphan*/ *,int,struct swap_info_struct*) ; 
 int /*<<< orphan*/  block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int set_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int claim_swapfile(struct swap_info_struct *p, struct inode *inode)
{
	int error;

	if (S_ISBLK(inode->i_mode)) {
		p->bdev = bdgrab(I_BDEV(inode));
		error = blkdev_get(p->bdev,
				   FMODE_READ | FMODE_WRITE | FMODE_EXCL, p);
		if (error < 0) {
			p->bdev = NULL;
			return error;
		}
		p->old_block_size = block_size(p->bdev);
		error = set_blocksize(p->bdev, PAGE_SIZE);
		if (error < 0)
			return error;
		p->flags |= SWP_BLKDEV;
	} else if (S_ISREG(inode->i_mode)) {
		p->bdev = inode->i_sb->s_bdev;
	}

	inode_lock(inode);
	if (IS_SWAPFILE(inode))
		return -EBUSY;

	return 0;
}