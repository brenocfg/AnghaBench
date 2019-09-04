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
 int lock_stripe_add (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  rmw_work ; 
 int /*<<< orphan*/  start_async_work (struct btrfs_raid_bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int partial_stripe_write(struct btrfs_raid_bio *rbio)
{
	int ret;

	ret = lock_stripe_add(rbio);
	if (ret == 0)
		start_async_work(rbio, rmw_work);
	return 0;
}