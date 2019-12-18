#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {TYPE_2__* transaction; int /*<<< orphan*/  delayed_ref_updates; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  pinned_extents; int /*<<< orphan*/  delalloc_root_lock; int /*<<< orphan*/  super_copy; } ;
struct TYPE_4__ {scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_block_group_cache {scalar_t__ cached; scalar_t__ disk_cache_state; scalar_t__ reserved; scalar_t__ pinned; int /*<<< orphan*/  dirty_list; TYPE_3__* space_info; int /*<<< orphan*/  lock; int /*<<< orphan*/  item; TYPE_1__ key; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ bytes_reserved; scalar_t__ bytes_used; scalar_t__ disk_used; int /*<<< orphan*/  total_bytes_pinned; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dirty_bgs_lock; int /*<<< orphan*/  dirty_bgs; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_NO ; 
 scalar_t__ BTRFS_DC_CLEAR ; 
 int /*<<< orphan*/  BTRFS_TOTAL_BYTES_PINNED_BATCH ; 
 int ENOENT ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  SPACE_CACHE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __GFP_NOFAIL ; 
 int btrfs_bg_type_to_factor (int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_cache_block_group (struct btrfs_block_group_cache*,int) ; 
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_mark_bg_unused (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_set_block_group_used (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_super_bytes_used (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_space_info_update_bytes_pinned (struct btrfs_fs_info*,TYPE_3__*,scalar_t__) ; 
 scalar_t__ btrfs_super_bytes_used (int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_update_delayed_refs_rsv (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_extent_dirty (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_update_block_group(struct btrfs_trans_handle *trans,
			     u64 bytenr, u64 num_bytes, int alloc)
{
	struct btrfs_fs_info *info = trans->fs_info;
	struct btrfs_block_group_cache *cache = NULL;
	u64 total = num_bytes;
	u64 old_val;
	u64 byte_in_group;
	int factor;
	int ret = 0;

	/* Block accounting for super block */
	spin_lock(&info->delalloc_root_lock);
	old_val = btrfs_super_bytes_used(info->super_copy);
	if (alloc)
		old_val += num_bytes;
	else
		old_val -= num_bytes;
	btrfs_set_super_bytes_used(info->super_copy, old_val);
	spin_unlock(&info->delalloc_root_lock);

	while (total) {
		cache = btrfs_lookup_block_group(info, bytenr);
		if (!cache) {
			ret = -ENOENT;
			break;
		}
		factor = btrfs_bg_type_to_factor(cache->flags);

		/*
		 * If this block group has free space cache written out, we
		 * need to make sure to load it if we are removing space.  This
		 * is because we need the unpinning stage to actually add the
		 * space back to the block group, otherwise we will leak space.
		 */
		if (!alloc && cache->cached == BTRFS_CACHE_NO)
			btrfs_cache_block_group(cache, 1);

		byte_in_group = bytenr - cache->key.objectid;
		WARN_ON(byte_in_group > cache->key.offset);

		spin_lock(&cache->space_info->lock);
		spin_lock(&cache->lock);

		if (btrfs_test_opt(info, SPACE_CACHE) &&
		    cache->disk_cache_state < BTRFS_DC_CLEAR)
			cache->disk_cache_state = BTRFS_DC_CLEAR;

		old_val = btrfs_block_group_used(&cache->item);
		num_bytes = min(total, cache->key.offset - byte_in_group);
		if (alloc) {
			old_val += num_bytes;
			btrfs_set_block_group_used(&cache->item, old_val);
			cache->reserved -= num_bytes;
			cache->space_info->bytes_reserved -= num_bytes;
			cache->space_info->bytes_used += num_bytes;
			cache->space_info->disk_used += num_bytes * factor;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);
		} else {
			old_val -= num_bytes;
			btrfs_set_block_group_used(&cache->item, old_val);
			cache->pinned += num_bytes;
			btrfs_space_info_update_bytes_pinned(info,
					cache->space_info, num_bytes);
			cache->space_info->bytes_used -= num_bytes;
			cache->space_info->disk_used -= num_bytes * factor;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);

			percpu_counter_add_batch(
					&cache->space_info->total_bytes_pinned,
					num_bytes,
					BTRFS_TOTAL_BYTES_PINNED_BATCH);
			set_extent_dirty(info->pinned_extents,
					 bytenr, bytenr + num_bytes - 1,
					 GFP_NOFS | __GFP_NOFAIL);
		}

		spin_lock(&trans->transaction->dirty_bgs_lock);
		if (list_empty(&cache->dirty_list)) {
			list_add_tail(&cache->dirty_list,
				      &trans->transaction->dirty_bgs);
			trans->delayed_ref_updates++;
			btrfs_get_block_group(cache);
		}
		spin_unlock(&trans->transaction->dirty_bgs_lock);

		/*
		 * No longer have used bytes in this block group, queue it for
		 * deletion. We do this after adding the block group to the
		 * dirty list to avoid races between cleaner kthread and space
		 * cache writeout.
		 */
		if (!alloc && old_val == 0)
			btrfs_mark_bg_unused(cache);

		btrfs_put_block_group(cache);
		total -= num_bytes;
		bytenr += num_bytes;
	}

	/* Modified block groups are accounted for in the delayed_refs_rsv. */
	btrfs_update_delayed_refs_rsv(trans);
	return ret;
}