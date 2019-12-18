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
struct dio {scalar_t__ op; scalar_t__ is_async; int /*<<< orphan*/  io_error; int /*<<< orphan*/  should_dirty; } ;
struct bio {scalar_t__ bi_status; int bi_opf; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ BLK_STS_AGAIN ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int REQ_NOWAIT ; 
 scalar_t__ REQ_OP_READ ; 
 int /*<<< orphan*/  bio_check_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_release_pages (struct bio*,int) ; 

__attribute__((used)) static blk_status_t dio_bio_complete(struct dio *dio, struct bio *bio)
{
	blk_status_t err = bio->bi_status;
	bool should_dirty = dio->op == REQ_OP_READ && dio->should_dirty;

	if (err) {
		if (err == BLK_STS_AGAIN && (bio->bi_opf & REQ_NOWAIT))
			dio->io_error = -EAGAIN;
		else
			dio->io_error = -EIO;
	}

	if (dio->is_async && should_dirty) {
		bio_check_pages_dirty(bio);	/* transfers ownership */
	} else {
		bio_release_pages(bio, should_dirty);
		bio_put(bio);
	}
	return err;
}