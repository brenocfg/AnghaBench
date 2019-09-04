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
struct inode {int /*<<< orphan*/  i_data; } ;
struct block_device {int /*<<< orphan*/ * bd_bdi; int /*<<< orphan*/  bd_list; } ;
struct TYPE_2__ {struct block_device bdev; } ;

/* Variables and functions */
 TYPE_1__* BDEV_I (struct inode*) ; 
 int /*<<< orphan*/  bdev_lock ; 
 int /*<<< orphan*/  bdi_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_detach_wb (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noop_backing_dev_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bdev_evict_inode(struct inode *inode)
{
	struct block_device *bdev = &BDEV_I(inode)->bdev;
	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode); /* is it needed here? */
	clear_inode(inode);
	spin_lock(&bdev_lock);
	list_del_init(&bdev->bd_list);
	spin_unlock(&bdev_lock);
	/* Detach inode from wb early as bdi_put() may free bdi->wb */
	inode_detach_wb(inode);
	if (bdev->bd_bdi != &noop_backing_dev_info) {
		bdi_put(bdev->bd_bdi);
		bdev->bd_bdi = &noop_backing_dev_info;
	}
}