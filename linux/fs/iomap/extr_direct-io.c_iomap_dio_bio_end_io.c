#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  work; } ;
struct TYPE_5__ {struct task_struct* waiter; } ;
struct iomap_dio {int flags; TYPE_4__ aio; TYPE_2__* iocb; TYPE_1__ submit; scalar_t__ wait_for_completion; int /*<<< orphan*/  ref; } ;
struct inode {TYPE_3__* i_sb; } ;
struct bio {scalar_t__ bi_status; struct iomap_dio* bi_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_dio_done_wq; } ;
struct TYPE_6__ {int /*<<< orphan*/  ki_filp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int IOMAP_DIO_DIRTY ; 
 int IOMAP_DIO_WRITE ; 
 int /*<<< orphan*/  WRITE_ONCE (struct task_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_check_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_release_pages (struct bio*,int) ; 
 int /*<<< orphan*/  blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  blk_wake_io_task (struct task_struct*) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_dio_complete_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iomap_dio_set_error (struct iomap_dio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iomap_dio_bio_end_io(struct bio *bio)
{
	struct iomap_dio *dio = bio->bi_private;
	bool should_dirty = (dio->flags & IOMAP_DIO_DIRTY);

	if (bio->bi_status)
		iomap_dio_set_error(dio, blk_status_to_errno(bio->bi_status));

	if (atomic_dec_and_test(&dio->ref)) {
		if (dio->wait_for_completion) {
			struct task_struct *waiter = dio->submit.waiter;
			WRITE_ONCE(dio->submit.waiter, NULL);
			blk_wake_io_task(waiter);
		} else if (dio->flags & IOMAP_DIO_WRITE) {
			struct inode *inode = file_inode(dio->iocb->ki_filp);

			INIT_WORK(&dio->aio.work, iomap_dio_complete_work);
			queue_work(inode->i_sb->s_dio_done_wq, &dio->aio.work);
		} else {
			iomap_dio_complete_work(&dio->aio.work);
		}
	}

	if (should_dirty) {
		bio_check_pages_dirty(bio);
	} else {
		bio_release_pages(bio, false);
		bio_put(bio);
	}
}