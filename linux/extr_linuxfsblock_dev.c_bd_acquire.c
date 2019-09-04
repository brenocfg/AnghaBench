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
struct inode {int /*<<< orphan*/  i_mapping; struct block_device* i_bdev; int /*<<< orphan*/  i_rdev; } ;
struct block_device {TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_forget (struct inode*) ; 
 int /*<<< orphan*/  bdev_lock ; 
 struct block_device* bdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdgrab (struct block_device*) ; 
 int /*<<< orphan*/  inode_unhashed (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct block_device *bd_acquire(struct inode *inode)
{
	struct block_device *bdev;

	spin_lock(&bdev_lock);
	bdev = inode->i_bdev;
	if (bdev && !inode_unhashed(bdev->bd_inode)) {
		bdgrab(bdev);
		spin_unlock(&bdev_lock);
		return bdev;
	}
	spin_unlock(&bdev_lock);

	/*
	 * i_bdev references block device inode that was already shut down
	 * (corresponding device got removed).  Remove the reference and look
	 * up block device inode again just in case new device got
	 * reestablished under the same device number.
	 */
	if (bdev)
		bd_forget(inode);

	bdev = bdget(inode->i_rdev);
	if (bdev) {
		spin_lock(&bdev_lock);
		if (!inode->i_bdev) {
			/*
			 * We take an additional reference to bd_inode,
			 * and it's released in clear_inode() of inode.
			 * So, we can access it via ->i_mapping always
			 * without igrab().
			 */
			bdgrab(bdev);
			inode->i_bdev = bdev;
			inode->i_mapping = bdev->bd_inode->i_mapping;
		}
		spin_unlock(&bdev_lock);
	}
	return bdev;
}