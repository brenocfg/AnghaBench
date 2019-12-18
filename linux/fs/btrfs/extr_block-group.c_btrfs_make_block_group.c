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
typedef  int u64 ;
struct btrfs_trans_handle {int /*<<< orphan*/  delayed_ref_updates; int /*<<< orphan*/  new_bgs; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int flags; int last_byte_to_unpin; int needs_free_space; int /*<<< orphan*/  bg_list; int /*<<< orphan*/  space_info; int /*<<< orphan*/  bytes_super; int /*<<< orphan*/  cached; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTRFS_CACHE_FINISHED ; 
 int /*<<< orphan*/  BTRFS_FIRST_CHUNK_TREE_OBJECTID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  add_new_free_space (struct btrfs_block_group_cache*,int,int) ; 
 int btrfs_add_block_group_cache (struct btrfs_fs_info*,struct btrfs_block_group_cache*) ; 
 struct btrfs_block_group_cache* btrfs_create_block_group_cache (struct btrfs_fs_info*,int,int) ; 
 int /*<<< orphan*/  btrfs_find_space_info (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  btrfs_free_excluded_extents (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_remove_free_space_cache (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_set_block_group_chunk_objectid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_block_group_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_set_block_group_used (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_trans_handle*) ; 
 scalar_t__ btrfs_should_fragment_free_space (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_update_delayed_refs_rsv (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_update_global_block_rsv (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_update_space_info (struct btrfs_fs_info*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int exclude_super_stripes (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  fragment_free_space (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  link_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_avail_alloc_bits (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  trace_btrfs_add_block_group (struct btrfs_fs_info*,struct btrfs_block_group_cache*,int) ; 

int btrfs_make_block_group(struct btrfs_trans_handle *trans, u64 bytes_used,
			   u64 type, u64 chunk_offset, u64 size)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_block_group_cache *cache;
	int ret;

	btrfs_set_log_full_commit(trans);

	cache = btrfs_create_block_group_cache(fs_info, chunk_offset, size);
	if (!cache)
		return -ENOMEM;

	btrfs_set_block_group_used(&cache->item, bytes_used);
	btrfs_set_block_group_chunk_objectid(&cache->item,
					     BTRFS_FIRST_CHUNK_TREE_OBJECTID);
	btrfs_set_block_group_flags(&cache->item, type);

	cache->flags = type;
	cache->last_byte_to_unpin = (u64)-1;
	cache->cached = BTRFS_CACHE_FINISHED;
	cache->needs_free_space = 1;
	ret = exclude_super_stripes(cache);
	if (ret) {
		/* We may have excluded something, so call this just in case */
		btrfs_free_excluded_extents(cache);
		btrfs_put_block_group(cache);
		return ret;
	}

	add_new_free_space(cache, chunk_offset, chunk_offset + size);

	btrfs_free_excluded_extents(cache);

#ifdef CONFIG_BTRFS_DEBUG
	if (btrfs_should_fragment_free_space(cache)) {
		u64 new_bytes_used = size - bytes_used;

		bytes_used += new_bytes_used >> 1;
		fragment_free_space(cache);
	}
#endif
	/*
	 * Ensure the corresponding space_info object is created and
	 * assigned to our block group. We want our bg to be added to the rbtree
	 * with its ->space_info set.
	 */
	cache->space_info = btrfs_find_space_info(fs_info, cache->flags);
	ASSERT(cache->space_info);

	ret = btrfs_add_block_group_cache(fs_info, cache);
	if (ret) {
		btrfs_remove_free_space_cache(cache);
		btrfs_put_block_group(cache);
		return ret;
	}

	/*
	 * Now that our block group has its ->space_info set and is inserted in
	 * the rbtree, update the space info's counters.
	 */
	trace_btrfs_add_block_group(fs_info, cache, 1);
	btrfs_update_space_info(fs_info, cache->flags, size, bytes_used,
				cache->bytes_super, &cache->space_info);
	btrfs_update_global_block_rsv(fs_info);

	link_block_group(cache);

	list_add_tail(&cache->bg_list, &trans->new_bgs);
	trans->delayed_ref_updates++;
	btrfs_update_delayed_refs_rsv(trans);

	set_avail_alloc_bits(fs_info, type);
	return 0;
}