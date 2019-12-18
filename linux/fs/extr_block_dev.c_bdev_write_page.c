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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct block_device_operations {int (* rw_page ) (struct block_device*,scalar_t__,struct page*,int /*<<< orphan*/ ) ;} ;
struct block_device {int /*<<< orphan*/  bd_queue; TYPE_1__* bd_disk; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {struct block_device_operations* fops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 scalar_t__ bdev_get_integrity (struct block_device*) ; 
 int blk_queue_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_page_buffers (struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 scalar_t__ get_start_sect (struct block_device*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int stub1 (struct block_device*,scalar_t__,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int bdev_write_page(struct block_device *bdev, sector_t sector,
			struct page *page, struct writeback_control *wbc)
{
	int result;
	const struct block_device_operations *ops = bdev->bd_disk->fops;

	if (!ops->rw_page || bdev_get_integrity(bdev))
		return -EOPNOTSUPP;
	result = blk_queue_enter(bdev->bd_queue, 0);
	if (result)
		return result;

	set_page_writeback(page);
	result = ops->rw_page(bdev, sector + get_start_sect(bdev), page,
			      REQ_OP_WRITE);
	if (result) {
		end_page_writeback(page);
	} else {
		clean_page_buffers(page);
		unlock_page(page);
	}
	blk_queue_exit(bdev->bd_queue);
	return result;
}