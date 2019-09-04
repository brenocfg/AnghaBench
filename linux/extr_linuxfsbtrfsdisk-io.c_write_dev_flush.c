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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct btrfs_device {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  flush_wait; int /*<<< orphan*/  bdev; struct bio* flush_bio; } ;
struct bio {int bi_opf; int /*<<< orphan*/ * bi_private; int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STATE_FLUSH_SENT ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_reset (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_empty_barrier ; 
 int /*<<< orphan*/  btrfsic_submit_bio (struct bio*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_dev_flush(struct btrfs_device *device)
{
	struct request_queue *q = bdev_get_queue(device->bdev);
	struct bio *bio = device->flush_bio;

	if (!test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		return;

	bio_reset(bio);
	bio->bi_end_io = btrfs_end_empty_barrier;
	bio_set_dev(bio, device->bdev);
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_PREFLUSH;
	init_completion(&device->flush_wait);
	bio->bi_private = &device->flush_wait;

	btrfsic_submit_bio(bio);
	set_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state);
}