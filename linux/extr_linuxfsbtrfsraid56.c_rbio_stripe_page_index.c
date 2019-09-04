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
struct btrfs_raid_bio {int stripe_npages; } ;

/* Variables and functions */

__attribute__((used)) static int rbio_stripe_page_index(struct btrfs_raid_bio *rbio, int stripe,
				  int index)
{
	return stripe * rbio->stripe_npages + index;
}