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
struct btrfs_raid_bio {int /*<<< orphan*/  bio_list; scalar_t__ generic_bio_cnt; int /*<<< orphan*/  fs_info; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  __free_raid_bio (struct btrfs_raid_bio*) ; 
 struct bio* bio_list_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_bio_counter_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rbio_endio_bio_list (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_stripe (struct btrfs_raid_bio*) ; 

__attribute__((used)) static void rbio_orig_end_io(struct btrfs_raid_bio *rbio, blk_status_t err)
{
	struct bio *cur = bio_list_get(&rbio->bio_list);
	struct bio *extra;

	if (rbio->generic_bio_cnt)
		btrfs_bio_counter_sub(rbio->fs_info, rbio->generic_bio_cnt);

	/*
	 * At this moment, rbio->bio_list is empty, however since rbio does not
	 * always have RBIO_RMW_LOCKED_BIT set and rbio is still linked on the
	 * hash list, rbio may be merged with others so that rbio->bio_list
	 * becomes non-empty.
	 * Once unlock_stripe() is done, rbio->bio_list will not be updated any
	 * more and we can call bio_endio() on all queued bios.
	 */
	unlock_stripe(rbio);
	extra = bio_list_get(&rbio->bio_list);
	__free_raid_bio(rbio);

	rbio_endio_bio_list(cur, err);
	if (extra)
		rbio_endio_bio_list(extra, err);
}