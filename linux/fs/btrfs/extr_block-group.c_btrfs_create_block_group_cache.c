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
typedef  void* u64 ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; void* offset; void* objectid; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  full_stripe_locks_root; int /*<<< orphan*/  free_space_lock; int /*<<< orphan*/  trimming; int /*<<< orphan*/  io_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  ro_list; int /*<<< orphan*/  bg_list; int /*<<< orphan*/  cluster_list; int /*<<< orphan*/  list; int /*<<< orphan*/  data_rwsem; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  full_stripe_len; struct btrfs_fs_info* fs_info; TYPE_1__ key; void* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_ITEM_KEY ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_full_stripe_len (struct btrfs_fs_info*,void*) ; 
 int /*<<< orphan*/  btrfs_init_free_space_ctl (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_init_full_stripe_locks_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_block_group_cache*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_free_space_tree_thresholds (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_block_group_cache *btrfs_create_block_group_cache(
		struct btrfs_fs_info *fs_info, u64 start, u64 size)
{
	struct btrfs_block_group_cache *cache;

	cache = kzalloc(sizeof(*cache), GFP_NOFS);
	if (!cache)
		return NULL;

	cache->free_space_ctl = kzalloc(sizeof(*cache->free_space_ctl),
					GFP_NOFS);
	if (!cache->free_space_ctl) {
		kfree(cache);
		return NULL;
	}

	cache->key.objectid = start;
	cache->key.offset = size;
	cache->key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;

	cache->fs_info = fs_info;
	cache->full_stripe_len = btrfs_full_stripe_len(fs_info, start);
	set_free_space_tree_thresholds(cache);

	atomic_set(&cache->count, 1);
	spin_lock_init(&cache->lock);
	init_rwsem(&cache->data_rwsem);
	INIT_LIST_HEAD(&cache->list);
	INIT_LIST_HEAD(&cache->cluster_list);
	INIT_LIST_HEAD(&cache->bg_list);
	INIT_LIST_HEAD(&cache->ro_list);
	INIT_LIST_HEAD(&cache->dirty_list);
	INIT_LIST_HEAD(&cache->io_list);
	btrfs_init_free_space_ctl(cache);
	atomic_set(&cache->trimming, 0);
	mutex_init(&cache->free_space_lock);
	btrfs_init_full_stripe_locks_tree(&cache->full_stripe_locks_root);

	return cache;
}