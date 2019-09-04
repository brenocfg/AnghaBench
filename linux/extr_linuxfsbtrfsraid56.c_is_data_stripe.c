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
struct btrfs_raid_bio {int nr_data; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_data_stripe(struct btrfs_raid_bio *rbio, int stripe)
{
	if (stripe >= 0 && stripe < rbio->nr_data)
		return 1;
	return 0;
}