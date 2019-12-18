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
struct task_struct {int dummy; } ;
struct kiocb {int /*<<< orphan*/  (* ki_complete ) (struct kiocb*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ki_pos; } ;
struct bio {scalar_t__ bi_status; struct blkdev_dio* bi_private; } ;
struct blkdev_dio {int should_dirty; struct task_struct* waiter; struct bio bio; scalar_t__ multi_bio; struct kiocb* iocb; scalar_t__ size; int /*<<< orphan*/  is_sync; int /*<<< orphan*/  ref; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (struct task_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_check_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_release_pages (struct bio*,int) ; 
 scalar_t__ blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  blk_wake_io_task (struct task_struct*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct kiocb*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blkdev_bio_end_io(struct bio *bio)
{
	struct blkdev_dio *dio = bio->bi_private;
	bool should_dirty = dio->should_dirty;

	if (bio->bi_status && !dio->bio.bi_status)
		dio->bio.bi_status = bio->bi_status;

	if (!dio->multi_bio || atomic_dec_and_test(&dio->ref)) {
		if (!dio->is_sync) {
			struct kiocb *iocb = dio->iocb;
			ssize_t ret;

			if (likely(!dio->bio.bi_status)) {
				ret = dio->size;
				iocb->ki_pos += ret;
			} else {
				ret = blk_status_to_errno(dio->bio.bi_status);
			}

			dio->iocb->ki_complete(iocb, ret, 0);
			if (dio->multi_bio)
				bio_put(&dio->bio);
		} else {
			struct task_struct *waiter = dio->waiter;

			WRITE_ONCE(dio->waiter, NULL);
			blk_wake_io_task(waiter);
		}
	}

	if (should_dirty) {
		bio_check_pages_dirty(bio);
	} else {
		bio_release_pages(bio, false);
		bio_put(bio);
	}
}