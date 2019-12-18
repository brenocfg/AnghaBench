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
struct extent_buffer {int dummy; } ;
struct btrfs_root {int ino_cache_progress; int highest_objectid; int /*<<< orphan*/  ino_cache_wait; int /*<<< orphan*/  ino_cache_lock; int /*<<< orphan*/  ino_cache_state; struct btrfs_free_space_ctl* free_ino_ctl; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int skip_locking; int search_commit_root; int* slots; struct extent_buffer** nodes; int /*<<< orphan*/  reada; } ;
struct btrfs_key {int objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_fs_info {int /*<<< orphan*/  commit_root_sem; } ;
struct btrfs_free_space_ctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_CACHE_FINISHED ; 
 int BTRFS_FIRST_FREE_OBJECTID ; 
 scalar_t__ BTRFS_INODE_ITEM_KEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int /*<<< orphan*/  READA_FORWARD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __btrfs_add_free_space (struct btrfs_fs_info*,struct btrfs_free_space_ctl*,int,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_fs_closing (struct btrfs_fs_info*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int btrfs_next_leaf (struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_transaction_in_commit (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_unpin_free_ino (struct btrfs_root*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_caching_thread (struct btrfs_root*) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caching_kthread(void *data)
{
	struct btrfs_root *root = data;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct btrfs_key key;
	struct btrfs_path *path;
	struct extent_buffer *leaf;
	u64 last = (u64)-1;
	int slot;
	int ret;

	if (!btrfs_test_opt(fs_info, INODE_MAP_CACHE))
		return 0;

	path = btrfs_alloc_path();
	if (!path) {
		fail_caching_thread(root);
		return -ENOMEM;
	}

	/* Since the commit root is read-only, we can safely skip locking. */
	path->skip_locking = 1;
	path->search_commit_root = 1;
	path->reada = READA_FORWARD;

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.offset = 0;
	key.type = BTRFS_INODE_ITEM_KEY;
again:
	/* need to make sure the commit_root doesn't disappear */
	down_read(&fs_info->commit_root_sem);

	ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	if (ret < 0)
		goto out;

	while (1) {
		if (btrfs_fs_closing(fs_info))
			goto out;

		leaf = path->nodes[0];
		slot = path->slots[0];
		if (slot >= btrfs_header_nritems(leaf)) {
			ret = btrfs_next_leaf(root, path);
			if (ret < 0)
				goto out;
			else if (ret > 0)
				break;

			if (need_resched() ||
			    btrfs_transaction_in_commit(fs_info)) {
				leaf = path->nodes[0];

				if (WARN_ON(btrfs_header_nritems(leaf) == 0))
					break;

				/*
				 * Save the key so we can advances forward
				 * in the next search.
				 */
				btrfs_item_key_to_cpu(leaf, &key, 0);
				btrfs_release_path(path);
				root->ino_cache_progress = last;
				up_read(&fs_info->commit_root_sem);
				schedule_timeout(1);
				goto again;
			} else
				continue;
		}

		btrfs_item_key_to_cpu(leaf, &key, slot);

		if (key.type != BTRFS_INODE_ITEM_KEY)
			goto next;

		if (key.objectid >= root->highest_objectid)
			break;

		if (last != (u64)-1 && last + 1 != key.objectid) {
			__btrfs_add_free_space(fs_info, ctl, last + 1,
					       key.objectid - last - 1);
			wake_up(&root->ino_cache_wait);
		}

		last = key.objectid;
next:
		path->slots[0]++;
	}

	if (last < root->highest_objectid - 1) {
		__btrfs_add_free_space(fs_info, ctl, last + 1,
				       root->highest_objectid - last - 1);
	}

	spin_lock(&root->ino_cache_lock);
	root->ino_cache_state = BTRFS_CACHE_FINISHED;
	spin_unlock(&root->ino_cache_lock);

	root->ino_cache_progress = (u64)-1;
	btrfs_unpin_free_ino(root);
out:
	wake_up(&root->ino_cache_wait);
	up_read(&fs_info->commit_root_sem);

	btrfs_free_path(path);

	return ret;
}