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
typedef  int u64 ;
struct btrfs_raid_bio {TYPE_1__* bbio; } ;
struct TYPE_2__ {int* raid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_STRIPE_HASH_TABLE_BITS ; 
 int hash_64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbio_bucket(struct btrfs_raid_bio *rbio)
{
	u64 num = rbio->bbio->raid_map[0];

	/*
	 * we shift down quite a bit.  We're using byte
	 * addressing, and most of the lower bits are zeros.
	 * This tends to upset hash_64, and it consistently
	 * returns just one or two different values.
	 *
	 * shifting off the lower bits fixes things.
	 */
	return hash_64(num >> 16, BTRFS_STRIPE_HASH_TABLE_BITS);
}