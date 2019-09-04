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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/ * i_mapping; struct block_device* i_bdev; int /*<<< orphan*/  i_sb; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_lock ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  sb_is_blkdev_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bd_forget(struct inode *inode)
{
	struct block_device *bdev = NULL;

	spin_lock(&bdev_lock);
	if (!sb_is_blkdev_sb(inode->i_sb))
		bdev = inode->i_bdev;
	inode->i_bdev = NULL;
	inode->i_mapping = &inode->i_data;
	spin_unlock(&bdev_lock);

	if (bdev)
		bdput(bdev);
}