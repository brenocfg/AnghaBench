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
struct btrfs_space_info {scalar_t__ bytes_pinned; scalar_t__ bytes_readonly; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytes_may_use; int /*<<< orphan*/  total_bytes_pinned; scalar_t__ max_extent_size; } ;
struct btrfs_block_rsv {int full; scalar_t__ size; scalar_t__ reserved; int /*<<< orphan*/  lock; struct btrfs_space_info* space_info; } ;
struct btrfs_fs_info {struct btrfs_block_rsv global_block_rsv; } ;
struct btrfs_free_cluster {int /*<<< orphan*/  lock; scalar_t__ fragmented; } ;
struct TYPE_2__ {scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_block_group_cache {scalar_t__ last_byte_to_unpin; scalar_t__ pinned; int /*<<< orphan*/  lock; scalar_t__ ro; struct btrfs_space_info* space_info; TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_TOTAL_BYTES_PINNED_BATCH ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_add_free_space (struct btrfs_block_group_cache*,scalar_t__,scalar_t__) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 struct btrfs_free_cluster* fetch_cluster_info (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_info_add_new_bytes (struct btrfs_fs_info*,struct btrfs_space_info*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int unpin_extent_range(struct btrfs_fs_info *fs_info,
			      u64 start, u64 end,
			      const bool return_free_space)
{
	struct btrfs_block_group_cache *cache = NULL;
	struct btrfs_space_info *space_info;
	struct btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	struct btrfs_free_cluster *cluster = NULL;
	u64 len;
	u64 total_unpinned = 0;
	u64 empty_cluster = 0;
	bool readonly;

	while (start <= end) {
		readonly = false;
		if (!cache ||
		    start >= cache->key.objectid + cache->key.offset) {
			if (cache)
				btrfs_put_block_group(cache);
			total_unpinned = 0;
			cache = btrfs_lookup_block_group(fs_info, start);
			BUG_ON(!cache); /* Logic error */

			cluster = fetch_cluster_info(fs_info,
						     cache->space_info,
						     &empty_cluster);
			empty_cluster <<= 1;
		}

		len = cache->key.objectid + cache->key.offset - start;
		len = min(len, end + 1 - start);

		if (start < cache->last_byte_to_unpin) {
			len = min(len, cache->last_byte_to_unpin - start);
			if (return_free_space)
				btrfs_add_free_space(cache, start, len);
		}

		start += len;
		total_unpinned += len;
		space_info = cache->space_info;

		/*
		 * If this space cluster has been marked as fragmented and we've
		 * unpinned enough in this block group to potentially allow a
		 * cluster to be created inside of it go ahead and clear the
		 * fragmented check.
		 */
		if (cluster && cluster->fragmented &&
		    total_unpinned > empty_cluster) {
			spin_lock(&cluster->lock);
			cluster->fragmented = 0;
			spin_unlock(&cluster->lock);
		}

		spin_lock(&space_info->lock);
		spin_lock(&cache->lock);
		cache->pinned -= len;
		space_info->bytes_pinned -= len;

		trace_btrfs_space_reservation(fs_info, "pinned",
					      space_info->flags, len, 0);
		space_info->max_extent_size = 0;
		percpu_counter_add_batch(&space_info->total_bytes_pinned,
			    -len, BTRFS_TOTAL_BYTES_PINNED_BATCH);
		if (cache->ro) {
			space_info->bytes_readonly += len;
			readonly = true;
		}
		spin_unlock(&cache->lock);
		if (!readonly && return_free_space &&
		    global_rsv->space_info == space_info) {
			u64 to_add = len;

			spin_lock(&global_rsv->lock);
			if (!global_rsv->full) {
				to_add = min(len, global_rsv->size -
					     global_rsv->reserved);
				global_rsv->reserved += to_add;
				space_info->bytes_may_use += to_add;
				if (global_rsv->reserved >= global_rsv->size)
					global_rsv->full = 1;
				trace_btrfs_space_reservation(fs_info,
							      "space_info",
							      space_info->flags,
							      to_add, 1);
				len -= to_add;
			}
			spin_unlock(&global_rsv->lock);
			/* Add to any tickets we may have */
			if (len)
				space_info_add_new_bytes(fs_info, space_info,
							 len);
		}
		spin_unlock(&space_info->lock);
	}

	if (cache)
		btrfs_put_block_group(cache);
	return 0;
}