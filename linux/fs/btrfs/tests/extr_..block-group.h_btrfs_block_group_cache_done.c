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
struct btrfs_block_group_cache {scalar_t__ cached; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_ERROR ; 
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline int btrfs_block_group_cache_done(
		struct btrfs_block_group_cache *cache)
{
	smp_mb();
	return cache->cached == BTRFS_CACHE_FINISHED ||
		cache->cached == BTRFS_CACHE_ERROR;
}