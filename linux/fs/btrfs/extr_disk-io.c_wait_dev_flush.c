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
struct btrfs_device {int /*<<< orphan*/  flush_wait; int /*<<< orphan*/  dev_state; struct bio* flush_bio; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BTRFS_DEV_STATE_FLUSH_SENT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t wait_dev_flush(struct btrfs_device *device)
{
	struct bio *bio = device->flush_bio;

	if (!test_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state))
		return BLK_STS_OK;

	clear_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state);
	wait_for_completion_io(&device->flush_wait);

	return bio->bi_status;
}