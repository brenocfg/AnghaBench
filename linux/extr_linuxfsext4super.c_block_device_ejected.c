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
struct super_block {TYPE_1__* s_bdev; } ;
struct inode {int dummy; } ;
struct backing_dev_info {int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {struct inode* bd_inode; } ;

/* Variables and functions */
 struct backing_dev_info* inode_to_bdi (struct inode*) ; 

__attribute__((used)) static int block_device_ejected(struct super_block *sb)
{
	struct inode *bd_inode = sb->s_bdev->bd_inode;
	struct backing_dev_info *bdi = inode_to_bdi(bd_inode);

	return bdi->dev == NULL;
}