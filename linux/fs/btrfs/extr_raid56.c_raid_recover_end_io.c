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
struct btrfs_raid_bio {TYPE_1__* bbio; int /*<<< orphan*/  error; int /*<<< orphan*/  stripes_pending; } ;
struct bio {scalar_t__ bi_status; struct btrfs_raid_bio* bi_private; } ;
struct TYPE_2__ {scalar_t__ max_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  __raid_recover_end_io (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  fail_bio_stripe (struct btrfs_raid_bio*,struct bio*) ; 
 int /*<<< orphan*/  rbio_orig_end_io (struct btrfs_raid_bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bio_pages_uptodate (struct bio*) ; 

__attribute__((used)) static void raid_recover_end_io(struct bio *bio)
{
	struct btrfs_raid_bio *rbio = bio->bi_private;

	/*
	 * we only read stripe pages off the disk, set them
	 * up to date if there were no errors
	 */
	if (bio->bi_status)
		fail_bio_stripe(rbio, bio);
	else
		set_bio_pages_uptodate(bio);
	bio_put(bio);

	if (!atomic_dec_and_test(&rbio->stripes_pending))
		return;

	if (atomic_read(&rbio->error) > rbio->bbio->max_errors)
		rbio_orig_end_io(rbio, BLK_STS_IOERR);
	else
		__raid_recover_end_io(rbio);
}