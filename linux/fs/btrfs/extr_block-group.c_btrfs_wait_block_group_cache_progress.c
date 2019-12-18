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
typedef  scalar_t__ u64 ;
struct btrfs_caching_control {int /*<<< orphan*/  wait; } ;
struct btrfs_block_group_cache {TYPE_1__* free_space_ctl; } ;
struct TYPE_2__ {scalar_t__ free_space; } ;

/* Variables and functions */
 scalar_t__ btrfs_block_group_cache_done (struct btrfs_block_group_cache*) ; 
 struct btrfs_caching_control* btrfs_get_caching_control (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_put_caching_control (struct btrfs_caching_control*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void btrfs_wait_block_group_cache_progress(struct btrfs_block_group_cache *cache,
					   u64 num_bytes)
{
	struct btrfs_caching_control *caching_ctl;

	caching_ctl = btrfs_get_caching_control(cache);
	if (!caching_ctl)
		return;

	wait_event(caching_ctl->wait, btrfs_block_group_cache_done(cache) ||
		   (cache->free_space_ctl->free_space >= num_bytes));

	btrfs_put_caching_control(caching_ctl);
}