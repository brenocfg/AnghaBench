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
struct inode {int i_state; int /*<<< orphan*/  i_lock; } ;
struct block_device {struct inode* bd_inode; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int I_DIRTY ; 
 int /*<<< orphan*/  bdevname (struct block_device*,char*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int write_inode_now (struct inode*,int) ; 

__attribute__((used)) static void bdev_write_inode(struct block_device *bdev)
{
	struct inode *inode = bdev->bd_inode;
	int ret;

	spin_lock(&inode->i_lock);
	while (inode->i_state & I_DIRTY) {
		spin_unlock(&inode->i_lock);
		ret = write_inode_now(inode, true);
		if (ret) {
			char name[BDEVNAME_SIZE];
			pr_warn_ratelimited("VFS: Dirty inode writeback failed "
					    "for block device %s (err=%d).\n",
					    bdevname(bdev, name), ret);
		}
		spin_lock(&inode->i_lock);
	}
	spin_unlock(&inode->i_lock);
}