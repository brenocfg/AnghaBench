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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {scalar_t__ ino_cache_state; TYPE_1__ root_key; int /*<<< orphan*/  ino_cache_wait; int /*<<< orphan*/  ino_cache_lock; struct btrfs_free_space_ctl* free_ino_ctl; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_free_space_ctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 scalar_t__ BTRFS_CACHE_NO ; 
 scalar_t__ BTRFS_CACHE_STARTED ; 
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  __btrfs_add_free_space (struct btrfs_fs_info*,struct btrfs_free_space_ctl*,scalar_t__,scalar_t__) ; 
 int btrfs_find_free_objectid (struct btrfs_root*,scalar_t__*) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caching_kthread ; 
 int /*<<< orphan*/  fail_caching_thread (struct btrfs_root*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct btrfs_root*,char*,int /*<<< orphan*/ ) ; 
 int load_free_ino_cache (struct btrfs_fs_info*,struct btrfs_root*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_caching(struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct task_struct *tsk;
	int ret;
	u64 objectid;

	if (!btrfs_test_opt(fs_info, INODE_MAP_CACHE))
		return;

	spin_lock(&root->ino_cache_lock);
	if (root->ino_cache_state != BTRFS_CACHE_NO) {
		spin_unlock(&root->ino_cache_lock);
		return;
	}

	root->ino_cache_state = BTRFS_CACHE_STARTED;
	spin_unlock(&root->ino_cache_lock);

	ret = load_free_ino_cache(fs_info, root);
	if (ret == 1) {
		spin_lock(&root->ino_cache_lock);
		root->ino_cache_state = BTRFS_CACHE_FINISHED;
		spin_unlock(&root->ino_cache_lock);
		wake_up(&root->ino_cache_wait);
		return;
	}

	/*
	 * It can be quite time-consuming to fill the cache by searching
	 * through the extent tree, and this can keep ino allocation path
	 * waiting. Therefore at start we quickly find out the highest
	 * inode number and we know we can use inode numbers which fall in
	 * [highest_ino + 1, BTRFS_LAST_FREE_OBJECTID].
	 */
	ret = btrfs_find_free_objectid(root, &objectid);
	if (!ret && objectid <= BTRFS_LAST_FREE_OBJECTID) {
		__btrfs_add_free_space(fs_info, ctl, objectid,
				       BTRFS_LAST_FREE_OBJECTID - objectid + 1);
		wake_up(&root->ino_cache_wait);
	}

	tsk = kthread_run(caching_kthread, root, "btrfs-ino-cache-%llu",
			  root->root_key.objectid);
	if (IS_ERR(tsk))
		fail_caching_thread(root);
}