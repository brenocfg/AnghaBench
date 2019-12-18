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
struct request {unsigned int nr_phys_segments; scalar_t__ rq_disk; int /*<<< orphan*/  ioprio; struct bio* biotail; struct bio* bio; int /*<<< orphan*/  __data_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {scalar_t__ bi_disk; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_prio (struct bio*) ; 

__attribute__((used)) static inline void blk_rq_bio_prep(struct request *rq, struct bio *bio,
		unsigned int nr_segs)
{
	rq->nr_phys_segments = nr_segs;
	rq->__data_len = bio->bi_iter.bi_size;
	rq->bio = rq->biotail = bio;
	rq->ioprio = bio_prio(bio);

	if (bio->bi_disk)
		rq->rq_disk = bio->bi_disk;
}