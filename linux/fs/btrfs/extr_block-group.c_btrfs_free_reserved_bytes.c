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
typedef  scalar_t__ u64 ;
struct btrfs_space_info {int /*<<< orphan*/  lock; scalar_t__ max_extent_size; int /*<<< orphan*/  bytes_reserved; int /*<<< orphan*/  bytes_readonly; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  delalloc_bytes; int /*<<< orphan*/  reserved; scalar_t__ ro; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_free_reserved_bytes(struct btrfs_block_group_cache *cache,
			       u64 num_bytes, int delalloc)
{
	struct btrfs_space_info *space_info = cache->space_info;

	spin_lock(&space_info->lock);
	spin_lock(&cache->lock);
	if (cache->ro)
		space_info->bytes_readonly += num_bytes;
	cache->reserved -= num_bytes;
	space_info->bytes_reserved -= num_bytes;
	space_info->max_extent_size = 0;

	if (delalloc)
		cache->delalloc_bytes -= num_bytes;
	spin_unlock(&cache->lock);
	spin_unlock(&space_info->lock);
}