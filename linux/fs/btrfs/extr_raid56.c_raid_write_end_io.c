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
struct btrfs_raid_bio {scalar_t__ operation; int /*<<< orphan*/  error; TYPE_1__* bbio; int /*<<< orphan*/  stripes_pending; } ;
struct bio {scalar_t__ bi_status; struct btrfs_raid_bio* bi_private; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {int max_errors; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BTRFS_RBIO_PARITY_SCRUB ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  fail_bio_stripe (struct btrfs_raid_bio*,struct bio*) ; 
 int /*<<< orphan*/  rbio_orig_end_io (struct btrfs_raid_bio*,scalar_t__) ; 

__attribute__((used)) static void raid_write_end_io(struct bio *bio)
{
	struct btrfs_raid_bio *rbio = bio->bi_private;
	blk_status_t err = bio->bi_status;
	int max_errors;

	if (err)
		fail_bio_stripe(rbio, bio);

	bio_put(bio);

	if (!atomic_dec_and_test(&rbio->stripes_pending))
		return;

	err = BLK_STS_OK;

	/* OK, we have read all the stripes we need to. */
	max_errors = (rbio->operation == BTRFS_RBIO_PARITY_SCRUB) ?
		     0 : rbio->bbio->max_errors;
	if (atomic_read(&rbio->error) > max_errors)
		err = BLK_STS_IOERR;

	rbio_orig_end_io(rbio, err);
}