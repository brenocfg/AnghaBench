#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct btrfs_dio_private {int errors; int /*<<< orphan*/  orig_bio; TYPE_3__* dio_bio; int /*<<< orphan*/  pending_bios; int /*<<< orphan*/  inode; scalar_t__ (* subio_endio ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  bi_size; scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; int /*<<< orphan*/  bi_opf; scalar_t__ bi_status; struct btrfs_dio_private* bi_private; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_9__ {TYPE_1__* root; } ;
struct TYPE_8__ {int /*<<< orphan*/  bi_status; } ;
struct TYPE_6__ {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 TYPE_4__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_io_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_4__*) ; 
 int /*<<< orphan*/  btrfs_io_bio (struct bio*) ; 
 int /*<<< orphan*/  btrfs_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void btrfs_end_dio_bio(struct bio *bio)
{
	struct btrfs_dio_private *dip = bio->bi_private;
	blk_status_t err = bio->bi_status;

	if (err)
		btrfs_warn(BTRFS_I(dip->inode)->root->fs_info,
			   "direct IO failed ino %llu rw %d,%u sector %#Lx len %u err no %d",
			   btrfs_ino(BTRFS_I(dip->inode)), bio_op(bio),
			   bio->bi_opf,
			   (unsigned long long)bio->bi_iter.bi_sector,
			   bio->bi_iter.bi_size, err);

	if (dip->subio_endio)
		err = dip->subio_endio(dip->inode, btrfs_io_bio(bio), err);

	if (err) {
		/*
		 * We want to perceive the errors flag being set before
		 * decrementing the reference count. We don't need a barrier
		 * since atomic operations with a return value are fully
		 * ordered as per atomic_t.txt
		 */
		dip->errors = 1;
	}

	/* if there are more bios still pending for this dio, just exit */
	if (!atomic_dec_and_test(&dip->pending_bios))
		goto out;

	if (dip->errors) {
		bio_io_error(dip->orig_bio);
	} else {
		dip->dio_bio->bi_status = BLK_STS_OK;
		bio_endio(dip->orig_bio);
	}
out:
	bio_put(bio);
}