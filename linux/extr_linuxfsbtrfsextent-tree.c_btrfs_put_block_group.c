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
struct TYPE_2__ {int /*<<< orphan*/  root; } ;
struct btrfs_block_group_cache {scalar_t__ pinned; scalar_t__ reserved; struct btrfs_block_group_cache* free_space_ctl; TYPE_1__ full_stripe_locks_root; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_block_group_cache*) ; 

void btrfs_put_block_group(struct btrfs_block_group_cache *cache)
{
	if (atomic_dec_and_test(&cache->count)) {
		WARN_ON(cache->pinned > 0);
		WARN_ON(cache->reserved > 0);

		/*
		 * If not empty, someone is still holding mutex of
		 * full_stripe_lock, which can only be released by caller.
		 * And it will definitely cause use-after-free when caller
		 * tries to release full stripe lock.
		 *
		 * No better way to resolve, but only to warn.
		 */
		WARN_ON(!RB_EMPTY_ROOT(&cache->full_stripe_locks_root.root));
		kfree(cache->free_space_ctl);
		kfree(cache);
	}
}