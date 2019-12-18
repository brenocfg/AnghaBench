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
 int /*<<< orphan*/  lock_stripe_add (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  scrub_parity_work ; 
 int /*<<< orphan*/  start_async_work (struct btrfs_raid_bio*,int /*<<< orphan*/ ) ; 

void raid56_parity_submit_scrub_rbio(struct btrfs_raid_bio *rbio)
{
	if (!lock_stripe_add(rbio))
		start_async_work(rbio, scrub_parity_work);
}