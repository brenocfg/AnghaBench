#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dio_submit {int /*<<< orphan*/  cur_page_fs_offset; int /*<<< orphan*/  logical_offset_in_bio; struct bio* bio; } ;
struct dio {TYPE_1__* iocb; scalar_t__ is_async; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  op; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_write_hint; int /*<<< orphan*/  bi_end_io; TYPE_2__ bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {int /*<<< orphan*/  ki_hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dio_bio_end_aio ; 
 int /*<<< orphan*/  dio_bio_end_io ; 

__attribute__((used)) static inline void
dio_bio_alloc(struct dio *dio, struct dio_submit *sdio,
	      struct block_device *bdev,
	      sector_t first_sector, int nr_vecs)
{
	struct bio *bio;

	/*
	 * bio_alloc() is guaranteed to return a bio when allowed to sleep and
	 * we request a valid number of vectors.
	 */
	bio = bio_alloc(GFP_KERNEL, nr_vecs);

	bio_set_dev(bio, bdev);
	bio->bi_iter.bi_sector = first_sector;
	bio_set_op_attrs(bio, dio->op, dio->op_flags);
	if (dio->is_async)
		bio->bi_end_io = dio_bio_end_aio;
	else
		bio->bi_end_io = dio_bio_end_io;

	bio->bi_write_hint = dio->iocb->ki_hint;

	sdio->bio = bio;
	sdio->logical_offset_in_bio = sdio->cur_page_fs_offset;
}