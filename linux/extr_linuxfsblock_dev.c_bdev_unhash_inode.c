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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_test ; 
 int /*<<< orphan*/  blockdev_superblock ; 
 int /*<<< orphan*/  hash (int /*<<< orphan*/ ) ; 
 struct inode* ilookup5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  remove_inode_hash (struct inode*) ; 

void bdev_unhash_inode(dev_t dev)
{
	struct inode *inode;

	inode = ilookup5(blockdev_superblock, hash(dev), bdev_test, &dev);
	if (inode) {
		remove_inode_hash(inode);
		iput(inode);
	}
}