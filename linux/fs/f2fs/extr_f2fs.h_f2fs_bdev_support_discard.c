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
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 scalar_t__ bdev_is_zoned (struct block_device*) ; 
 scalar_t__ blk_queue_discard (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_bdev_support_discard(struct block_device *bdev)
{
	return blk_queue_discard(bdev_get_queue(bdev)) ||
	       bdev_is_zoned(bdev);
}