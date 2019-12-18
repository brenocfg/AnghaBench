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
struct btrfs_raid_bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_raid_bio (struct btrfs_raid_bio*) ; 
 int alloc_rbio_parity_pages (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  finish_rmw (struct btrfs_raid_bio*) ; 
 int lock_stripe_add (struct btrfs_raid_bio*) ; 

__attribute__((used)) static int full_stripe_write(struct btrfs_raid_bio *rbio)
{
	int ret;

	ret = alloc_rbio_parity_pages(rbio);
	if (ret) {
		__free_raid_bio(rbio);
		return ret;
	}

	ret = lock_stripe_add(rbio);
	if (ret == 0)
		finish_rmw(rbio);
	return 0;
}