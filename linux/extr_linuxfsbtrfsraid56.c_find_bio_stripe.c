#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct btrfs_raid_bio {int stripe_len; TYPE_2__* bbio; } ;
struct btrfs_bio_stripe {int physical; TYPE_4__* dev; } ;
struct TYPE_5__ {int bi_sector; } ;
struct bio {scalar_t__ bi_disk; scalar_t__ bi_partno; TYPE_1__ bi_iter; } ;
struct TYPE_8__ {TYPE_3__* bdev; } ;
struct TYPE_7__ {scalar_t__ bd_disk; scalar_t__ bd_partno; } ;
struct TYPE_6__ {int num_stripes; struct btrfs_bio_stripe* stripes; } ;

/* Variables and functions */

__attribute__((used)) static int find_bio_stripe(struct btrfs_raid_bio *rbio,
			   struct bio *bio)
{
	u64 physical = bio->bi_iter.bi_sector;
	u64 stripe_start;
	int i;
	struct btrfs_bio_stripe *stripe;

	physical <<= 9;

	for (i = 0; i < rbio->bbio->num_stripes; i++) {
		stripe = &rbio->bbio->stripes[i];
		stripe_start = stripe->physical;
		if (physical >= stripe_start &&
		    physical < stripe_start + rbio->stripe_len &&
		    stripe->dev->bdev &&
		    bio->bi_disk == stripe->dev->bdev->bd_disk &&
		    bio->bi_partno == stripe->dev->bdev->bd_partno) {
			return i;
		}
	}
	return -1;
}