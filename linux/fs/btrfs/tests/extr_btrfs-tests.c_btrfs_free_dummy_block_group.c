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
struct btrfs_block_group_cache {struct btrfs_block_group_cache* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btrfs_remove_free_space_cache (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  kfree (struct btrfs_block_group_cache*) ; 

void btrfs_free_dummy_block_group(struct btrfs_block_group_cache *cache)
{
	if (!cache)
		return;
	__btrfs_remove_free_space_cache(cache->free_space_ctl);
	kfree(cache->free_space_ctl);
	kfree(cache);
}