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
struct btrfs_caching_control {int /*<<< orphan*/  wait; } ;
struct btrfs_block_group_cache {scalar_t__ cached; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_ERROR ; 
 int EIO ; 
 int /*<<< orphan*/  btrfs_block_group_cache_done (struct btrfs_block_group_cache*) ; 
 struct btrfs_caching_control* btrfs_get_caching_control (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_put_caching_control (struct btrfs_caching_control*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_wait_block_group_cache_done(struct btrfs_block_group_cache *cache)
{
	struct btrfs_caching_control *caching_ctl;
	int ret = 0;

	caching_ctl = btrfs_get_caching_control(cache);
	if (!caching_ctl)
		return (cache->cached == BTRFS_CACHE_ERROR) ? -EIO : 0;

	wait_event(caching_ctl->wait, btrfs_block_group_cache_done(cache));
	if (cache->cached == BTRFS_CACHE_ERROR)
		ret = -EIO;
	btrfs_put_caching_control(caching_ctl);
	return ret;
}