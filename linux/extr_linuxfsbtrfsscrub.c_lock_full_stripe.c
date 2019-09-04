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
typedef  int /*<<< orphan*/  u64 ;
struct full_stripe_lock {int /*<<< orphan*/  mutex; } ;
struct btrfs_full_stripe_locks_tree {int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int flags; struct btrfs_full_stripe_locks_tree full_stripe_locks_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int BTRFS_BLOCK_GROUP_RAID56_MASK ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct full_stripe_lock*) ; 
 int PTR_ERR (struct full_stripe_lock*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  get_full_stripe_logical (struct btrfs_block_group_cache*,int /*<<< orphan*/ ) ; 
 struct full_stripe_lock* insert_full_stripe_lock (struct btrfs_full_stripe_locks_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lock_full_stripe(struct btrfs_fs_info *fs_info, u64 bytenr,
			    bool *locked_ret)
{
	struct btrfs_block_group_cache *bg_cache;
	struct btrfs_full_stripe_locks_tree *locks_root;
	struct full_stripe_lock *existing;
	u64 fstripe_start;
	int ret = 0;

	*locked_ret = false;
	bg_cache = btrfs_lookup_block_group(fs_info, bytenr);
	if (!bg_cache) {
		ASSERT(0);
		return -ENOENT;
	}

	/* Profiles not based on parity don't need full stripe lock */
	if (!(bg_cache->flags & BTRFS_BLOCK_GROUP_RAID56_MASK))
		goto out;
	locks_root = &bg_cache->full_stripe_locks_root;

	fstripe_start = get_full_stripe_logical(bg_cache, bytenr);

	/* Now insert the full stripe lock */
	mutex_lock(&locks_root->lock);
	existing = insert_full_stripe_lock(locks_root, fstripe_start);
	mutex_unlock(&locks_root->lock);
	if (IS_ERR(existing)) {
		ret = PTR_ERR(existing);
		goto out;
	}
	mutex_lock(&existing->mutex);
	*locked_ret = true;
out:
	btrfs_put_block_group(bg_cache);
	return ret;
}