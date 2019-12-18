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
struct btrfs_raid_bio {scalar_t__ operation; int faila; int failb; TYPE_1__* bbio; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__* raid_map; } ;

/* Variables and functions */
 scalar_t__ BTRFS_RBIO_PARITY_SCRUB ; 
 scalar_t__ BTRFS_RBIO_READ_REBUILD ; 
 scalar_t__ BTRFS_RBIO_REBUILD_MISSING ; 
 int /*<<< orphan*/  RBIO_CACHE_BIT ; 
 int /*<<< orphan*/  RBIO_RMW_LOCKED_BIT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbio_can_merge(struct btrfs_raid_bio *last,
			  struct btrfs_raid_bio *cur)
{
	if (test_bit(RBIO_RMW_LOCKED_BIT, &last->flags) ||
	    test_bit(RBIO_RMW_LOCKED_BIT, &cur->flags))
		return 0;

	/*
	 * we can't merge with cached rbios, since the
	 * idea is that when we merge the destination
	 * rbio is going to run our IO for us.  We can
	 * steal from cached rbios though, other functions
	 * handle that.
	 */
	if (test_bit(RBIO_CACHE_BIT, &last->flags) ||
	    test_bit(RBIO_CACHE_BIT, &cur->flags))
		return 0;

	if (last->bbio->raid_map[0] !=
	    cur->bbio->raid_map[0])
		return 0;

	/* we can't merge with different operations */
	if (last->operation != cur->operation)
		return 0;
	/*
	 * We've need read the full stripe from the drive.
	 * check and repair the parity and write the new results.
	 *
	 * We're not allowed to add any new bios to the
	 * bio list here, anyone else that wants to
	 * change this stripe needs to do their own rmw.
	 */
	if (last->operation == BTRFS_RBIO_PARITY_SCRUB)
		return 0;

	if (last->operation == BTRFS_RBIO_REBUILD_MISSING)
		return 0;

	if (last->operation == BTRFS_RBIO_READ_REBUILD) {
		int fa = last->faila;
		int fb = last->failb;
		int cur_fa = cur->faila;
		int cur_fb = cur->failb;

		if (last->faila >= last->failb) {
			fa = last->failb;
			fb = last->faila;
		}

		if (cur->faila >= cur->failb) {
			cur_fa = cur->failb;
			cur_fb = cur->faila;
		}

		if (fa != cur_fa || fb != cur_fb)
			return 0;
	}
	return 1;
}