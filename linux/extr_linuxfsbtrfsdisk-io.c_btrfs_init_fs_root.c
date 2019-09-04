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
struct btrfs_subvolume_writers {int dummy; } ;
struct btrfs_root {scalar_t__ highest_objectid; int /*<<< orphan*/  objectid_mutex; int /*<<< orphan*/  anon_dev; int /*<<< orphan*/  ino_cache_wait; int /*<<< orphan*/  ino_cache_lock; struct btrfs_subvolume_writers* subv_writers; void* free_ino_ctl; void* free_ino_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct btrfs_subvolume_writers*) ; 
 int PTR_ERR (struct btrfs_subvolume_writers*) ; 
 struct btrfs_subvolume_writers* btrfs_alloc_subvolume_writers () ; 
 int btrfs_find_highest_objectid (struct btrfs_root*,scalar_t__*) ; 
 int /*<<< orphan*/  btrfs_init_free_ino_ctl (struct btrfs_root*) ; 
 int get_anon_bdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int btrfs_init_fs_root(struct btrfs_root *root)
{
	int ret;
	struct btrfs_subvolume_writers *writers;

	root->free_ino_ctl = kzalloc(sizeof(*root->free_ino_ctl), GFP_NOFS);
	root->free_ino_pinned = kzalloc(sizeof(*root->free_ino_pinned),
					GFP_NOFS);
	if (!root->free_ino_pinned || !root->free_ino_ctl) {
		ret = -ENOMEM;
		goto fail;
	}

	writers = btrfs_alloc_subvolume_writers();
	if (IS_ERR(writers)) {
		ret = PTR_ERR(writers);
		goto fail;
	}
	root->subv_writers = writers;

	btrfs_init_free_ino_ctl(root);
	spin_lock_init(&root->ino_cache_lock);
	init_waitqueue_head(&root->ino_cache_wait);

	ret = get_anon_bdev(&root->anon_dev);
	if (ret)
		goto fail;

	mutex_lock(&root->objectid_mutex);
	ret = btrfs_find_highest_objectid(root,
					&root->highest_objectid);
	if (ret) {
		mutex_unlock(&root->objectid_mutex);
		goto fail;
	}

	ASSERT(root->highest_objectid <= BTRFS_LAST_FREE_OBJECTID);

	mutex_unlock(&root->objectid_mutex);

	return 0;
fail:
	/* The caller is responsible to call btrfs_free_fs_root */
	return ret;
}