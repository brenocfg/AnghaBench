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
struct dio_submit {int /*<<< orphan*/  logical_offset_in_bio; scalar_t__ boundary; struct bio* bio; int /*<<< orphan*/  (* submit_io ) (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dio {scalar_t__ op; int /*<<< orphan*/  bio_cookie; int /*<<< orphan*/  inode; int /*<<< orphan*/  bio_disk; scalar_t__ should_dirty; scalar_t__ is_async; int /*<<< orphan*/  bio_lock; int /*<<< orphan*/  refcount; } ;
struct bio {int /*<<< orphan*/  bi_disk; struct dio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 scalar_t__ REQ_OP_READ ; 
 int /*<<< orphan*/  bio_set_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static inline void dio_bio_submit(struct dio *dio, struct dio_submit *sdio)
{
	struct bio *bio = sdio->bio;
	unsigned long flags;

	bio->bi_private = dio;

	spin_lock_irqsave(&dio->bio_lock, flags);
	dio->refcount++;
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	if (dio->is_async && dio->op == REQ_OP_READ && dio->should_dirty)
		bio_set_pages_dirty(bio);

	dio->bio_disk = bio->bi_disk;

	if (sdio->submit_io) {
		sdio->submit_io(bio, dio->inode, sdio->logical_offset_in_bio);
		dio->bio_cookie = BLK_QC_T_NONE;
	} else
		dio->bio_cookie = submit_bio(bio);

	sdio->bio = NULL;
	sdio->boundary = 0;
	sdio->logical_offset_in_bio = 0;
}