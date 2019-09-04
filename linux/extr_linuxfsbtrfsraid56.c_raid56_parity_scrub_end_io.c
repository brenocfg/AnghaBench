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
struct btrfs_raid_bio {int /*<<< orphan*/  stripes_pending; } ;
struct bio {scalar_t__ bi_status; struct btrfs_raid_bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  fail_bio_stripe (struct btrfs_raid_bio*,struct bio*) ; 
 int /*<<< orphan*/  set_bio_pages_uptodate (struct bio*) ; 
 int /*<<< orphan*/  validate_rbio_for_parity_scrub (struct btrfs_raid_bio*) ; 

__attribute__((used)) static void raid56_parity_scrub_end_io(struct bio *bio)
{
	struct btrfs_raid_bio *rbio = bio->bi_private;

	if (bio->bi_status)
		fail_bio_stripe(rbio, bio);
	else
		set_bio_pages_uptodate(bio);

	bio_put(bio);

	if (!atomic_dec_and_test(&rbio->stripes_pending))
		return;

	/*
	 * this will normally call finish_rmw to start our write
	 * but if there are any failed stripes we'll reconstruct
	 * from parity first
	 */
	validate_rbio_for_parity_scrub(rbio);
}