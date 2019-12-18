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
struct page {int dummy; } ;
struct block_device_operations {int (* rw_page ) (struct block_device*,scalar_t__,struct page*,int /*<<< orphan*/ ) ;} ;
struct block_device {int /*<<< orphan*/  bd_queue; TYPE_1__* bd_disk; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {struct block_device_operations* fops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ bdev_get_integrity (struct block_device*) ; 
 int blk_queue_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ get_start_sect (struct block_device*) ; 
 int stub1 (struct block_device*,scalar_t__,struct page*,int /*<<< orphan*/ ) ; 

int bdev_read_page(struct block_device *bdev, sector_t sector,
			struct page *page)
{
	const struct block_device_operations *ops = bdev->bd_disk->fops;
	int result = -EOPNOTSUPP;

	if (!ops->rw_page || bdev_get_integrity(bdev))
		return result;

	result = blk_queue_enter(bdev->bd_queue, 0);
	if (result)
		return result;
	result = ops->rw_page(bdev, sector + get_start_sect(bdev), page,
			      REQ_OP_READ);
	blk_queue_exit(bdev->bd_queue);
	return result;
}