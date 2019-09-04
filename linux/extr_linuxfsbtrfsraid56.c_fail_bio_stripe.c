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
struct bio {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int fail_rbio_index (struct btrfs_raid_bio*,int) ; 
 int find_bio_stripe (struct btrfs_raid_bio*,struct bio*) ; 

__attribute__((used)) static int fail_bio_stripe(struct btrfs_raid_bio *rbio,
			   struct bio *bio)
{
	int failed = find_bio_stripe(rbio, bio);

	if (failed < 0)
		return -EIO;

	return fail_rbio_index(rbio, failed);
}