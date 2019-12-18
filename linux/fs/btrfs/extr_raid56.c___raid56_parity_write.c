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
 int full_stripe_write (struct btrfs_raid_bio*) ; 
 int partial_stripe_write (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  rbio_is_full (struct btrfs_raid_bio*) ; 

__attribute__((used)) static int __raid56_parity_write(struct btrfs_raid_bio *rbio)
{
	/* head off into rmw land if we don't have a full stripe */
	if (!rbio_is_full(rbio))
		return partial_stripe_write(rbio);
	return full_stripe_write(rbio);
}