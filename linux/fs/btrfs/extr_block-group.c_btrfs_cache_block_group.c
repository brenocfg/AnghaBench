#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct btrfs_fs_info {int /*<<< orphan*/  caching_workers; int /*<<< orphan*/  commit_root_sem; int /*<<< orphan*/  caching_block_groups; } ;
struct btrfs_caching_control {int progress; int /*<<< orphan*/  work; int /*<<< orphan*/  list; int /*<<< orphan*/  count; int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; struct btrfs_block_group_cache* block_group; } ;
struct TYPE_3__ {int objectid; int offset; } ;
struct btrfs_block_group_cache {scalar_t__ cached; int last_byte_to_unpin; int has_caching_ctl; int /*<<< orphan*/  lock; struct btrfs_caching_control* caching_ctl; TYPE_2__* space_info; int /*<<< orphan*/  item; TYPE_1__ key; struct btrfs_fs_info* fs_info; } ;
struct TYPE_4__ {int bytes_used; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FAST ; 
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 scalar_t__ BTRFS_CACHE_NO ; 
 void* BTRFS_CACHE_STARTED ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPACE_CACHE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (struct btrfs_caching_control*) ; 
 int btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_cache_helper ; 
 int /*<<< orphan*/  btrfs_free_excluded_extents (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_put_caching_control (struct btrfs_caching_control*) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_should_fragment_free_space (struct btrfs_block_group_cache*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caching_thread ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fragment_free_space (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_caching_control*) ; 
 struct btrfs_caching_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int load_free_space_cache (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int btrfs_cache_block_group(struct btrfs_block_group_cache *cache,
			    int load_cache_only)
{
	DEFINE_WAIT(wait);
	struct btrfs_fs_info *fs_info = cache->fs_info;
	struct btrfs_caching_control *caching_ctl;
	int ret = 0;

	caching_ctl = kzalloc(sizeof(*caching_ctl), GFP_NOFS);
	if (!caching_ctl)
		return -ENOMEM;

	INIT_LIST_HEAD(&caching_ctl->list);
	mutex_init(&caching_ctl->mutex);
	init_waitqueue_head(&caching_ctl->wait);
	caching_ctl->block_group = cache;
	caching_ctl->progress = cache->key.objectid;
	refcount_set(&caching_ctl->count, 1);
	btrfs_init_work(&caching_ctl->work, btrfs_cache_helper,
			caching_thread, NULL, NULL);

	spin_lock(&cache->lock);
	/*
	 * This should be a rare occasion, but this could happen I think in the
	 * case where one thread starts to load the space cache info, and then
	 * some other thread starts a transaction commit which tries to do an
	 * allocation while the other thread is still loading the space cache
	 * info.  The previous loop should have kept us from choosing this block
	 * group, but if we've moved to the state where we will wait on caching
	 * block groups we need to first check if we're doing a fast load here,
	 * so we can wait for it to finish, otherwise we could end up allocating
	 * from a block group who's cache gets evicted for one reason or
	 * another.
	 */
	while (cache->cached == BTRFS_CACHE_FAST) {
		struct btrfs_caching_control *ctl;

		ctl = cache->caching_ctl;
		refcount_inc(&ctl->count);
		prepare_to_wait(&ctl->wait, &wait, TASK_UNINTERRUPTIBLE);
		spin_unlock(&cache->lock);

		schedule();

		finish_wait(&ctl->wait, &wait);
		btrfs_put_caching_control(ctl);
		spin_lock(&cache->lock);
	}

	if (cache->cached != BTRFS_CACHE_NO) {
		spin_unlock(&cache->lock);
		kfree(caching_ctl);
		return 0;
	}
	WARN_ON(cache->caching_ctl);
	cache->caching_ctl = caching_ctl;
	cache->cached = BTRFS_CACHE_FAST;
	spin_unlock(&cache->lock);

	if (btrfs_test_opt(fs_info, SPACE_CACHE)) {
		mutex_lock(&caching_ctl->mutex);
		ret = load_free_space_cache(cache);

		spin_lock(&cache->lock);
		if (ret == 1) {
			cache->caching_ctl = NULL;
			cache->cached = BTRFS_CACHE_FINISHED;
			cache->last_byte_to_unpin = (u64)-1;
			caching_ctl->progress = (u64)-1;
		} else {
			if (load_cache_only) {
				cache->caching_ctl = NULL;
				cache->cached = BTRFS_CACHE_NO;
			} else {
				cache->cached = BTRFS_CACHE_STARTED;
				cache->has_caching_ctl = 1;
			}
		}
		spin_unlock(&cache->lock);
#ifdef CONFIG_BTRFS_DEBUG
		if (ret == 1 &&
		    btrfs_should_fragment_free_space(cache)) {
			u64 bytes_used;

			spin_lock(&cache->space_info->lock);
			spin_lock(&cache->lock);
			bytes_used = cache->key.offset -
				btrfs_block_group_used(&cache->item);
			cache->space_info->bytes_used += bytes_used >> 1;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);
			fragment_free_space(cache);
		}
#endif
		mutex_unlock(&caching_ctl->mutex);

		wake_up(&caching_ctl->wait);
		if (ret == 1) {
			btrfs_put_caching_control(caching_ctl);
			btrfs_free_excluded_extents(cache);
			return 0;
		}
	} else {
		/*
		 * We're either using the free space tree or no caching at all.
		 * Set cached to the appropriate value and wakeup any waiters.
		 */
		spin_lock(&cache->lock);
		if (load_cache_only) {
			cache->caching_ctl = NULL;
			cache->cached = BTRFS_CACHE_NO;
		} else {
			cache->cached = BTRFS_CACHE_STARTED;
			cache->has_caching_ctl = 1;
		}
		spin_unlock(&cache->lock);
		wake_up(&caching_ctl->wait);
	}

	if (load_cache_only) {
		btrfs_put_caching_control(caching_ctl);
		return 0;
	}

	down_write(&fs_info->commit_root_sem);
	refcount_inc(&caching_ctl->count);
	list_add_tail(&caching_ctl->list, &fs_info->caching_block_groups);
	up_write(&fs_info->commit_root_sem);

	btrfs_get_block_group(cache);

	btrfs_queue_work(fs_info->caching_workers, &caching_ctl->work);

	return ret;
}