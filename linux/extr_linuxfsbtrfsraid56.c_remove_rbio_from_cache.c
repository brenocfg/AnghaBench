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
struct btrfs_stripe_hash_table {int /*<<< orphan*/  cache_lock; } ;
struct btrfs_raid_bio {TYPE_1__* fs_info; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct btrfs_stripe_hash_table* stripe_hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBIO_CACHE_BIT ; 
 int /*<<< orphan*/  __remove_rbio_from_cache (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_rbio_from_cache(struct btrfs_raid_bio *rbio)
{
	struct btrfs_stripe_hash_table *table;
	unsigned long flags;

	if (!test_bit(RBIO_CACHE_BIT, &rbio->flags))
		return;

	table = rbio->fs_info->stripe_hash_table;

	spin_lock_irqsave(&table->cache_lock, flags);
	__remove_rbio_from_cache(rbio);
	spin_unlock_irqrestore(&table->cache_lock, flags);
}