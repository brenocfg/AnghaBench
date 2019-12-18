#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct btrfs_trans_handle {TYPE_1__* transaction; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  disk_cache_state; int /*<<< orphan*/  io_list; } ;
struct TYPE_5__ {struct btrfs_root* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  cache_write_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DC_CLEAR ; 
 int /*<<< orphan*/  BTRFS_EXTENT_DATA_KEY ; 
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_i_size_write (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_wait_cache_io (struct btrfs_trans_handle*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ) ; 

int btrfs_truncate_free_space_cache(struct btrfs_trans_handle *trans,
				    struct btrfs_block_group_cache *block_group,
				    struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret = 0;
	bool locked = false;

	if (block_group) {
		struct btrfs_path *path = btrfs_alloc_path();

		if (!path) {
			ret = -ENOMEM;
			goto fail;
		}
		locked = true;
		mutex_lock(&trans->transaction->cache_write_mutex);
		if (!list_empty(&block_group->io_list)) {
			list_del_init(&block_group->io_list);

			btrfs_wait_cache_io(trans, block_group, path);
			btrfs_put_block_group(block_group);
		}

		/*
		 * now that we've truncated the cache away, its no longer
		 * setup or written
		 */
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_CLEAR;
		spin_unlock(&block_group->lock);
		btrfs_free_path(path);
	}

	btrfs_i_size_write(BTRFS_I(inode), 0);
	truncate_pagecache(inode, 0);

	/*
	 * We skip the throttling logic for free space cache inodes, so we don't
	 * need to check for -EAGAIN.
	 */
	ret = btrfs_truncate_inode_items(trans, root, inode,
					 0, BTRFS_EXTENT_DATA_KEY);
	if (ret)
		goto fail;

	ret = btrfs_update_inode(trans, root, inode);

fail:
	if (locked)
		mutex_unlock(&trans->transaction->cache_write_mutex);
	if (ret)
		btrfs_abort_transaction(trans, ret);

	return ret;
}