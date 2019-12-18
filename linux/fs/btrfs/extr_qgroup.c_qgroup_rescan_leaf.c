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
struct ulist {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; void* objectid; void* offset; } ;
struct TYPE_2__ {void* objectid; int /*<<< orphan*/  offset; int /*<<< orphan*/  type; } ;
struct btrfs_fs_info {TYPE_1__ qgroup_rescan_progress; void* nodesize; int /*<<< orphan*/  qgroup_rescan_lock; int /*<<< orphan*/  extent_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_ITEM_KEY ; 
 scalar_t__ BTRFS_METADATA_ITEM_KEY ; 
 int ENOMEM ; 
 struct extent_buffer* btrfs_clone_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_debug (struct btrfs_fs_info*,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int btrfs_find_all_roots (int /*<<< orphan*/ *,struct btrfs_fs_info*,void*,int /*<<< orphan*/ ,struct ulist**,int) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int btrfs_qgroup_account_extent (struct btrfs_trans_handle*,void*,void*,int /*<<< orphan*/ *,struct ulist*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot_for_read (int /*<<< orphan*/ ,TYPE_1__*,struct btrfs_path*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int is_last_leaf (struct btrfs_path*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qgroup_rescan_leaf(struct btrfs_trans_handle *trans,
			      struct btrfs_path *path)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_key found;
	struct extent_buffer *scratch_leaf = NULL;
	struct ulist *roots = NULL;
	u64 num_bytes;
	bool done;
	int slot;
	int ret;

	mutex_lock(&fs_info->qgroup_rescan_lock);
	ret = btrfs_search_slot_for_read(fs_info->extent_root,
					 &fs_info->qgroup_rescan_progress,
					 path, 1, 0);

	btrfs_debug(fs_info,
		"current progress key (%llu %u %llu), search_slot ret %d",
		fs_info->qgroup_rescan_progress.objectid,
		fs_info->qgroup_rescan_progress.type,
		fs_info->qgroup_rescan_progress.offset, ret);

	if (ret) {
		/*
		 * The rescan is about to end, we will not be scanning any
		 * further blocks. We cannot unset the RESCAN flag here, because
		 * we want to commit the transaction if everything went well.
		 * To make the live accounting work in this phase, we set our
		 * scan progress pointer such that every real extent objectid
		 * will be smaller.
		 */
		fs_info->qgroup_rescan_progress.objectid = (u64)-1;
		btrfs_release_path(path);
		mutex_unlock(&fs_info->qgroup_rescan_lock);
		return ret;
	}
	done = is_last_leaf(path);

	btrfs_item_key_to_cpu(path->nodes[0], &found,
			      btrfs_header_nritems(path->nodes[0]) - 1);
	fs_info->qgroup_rescan_progress.objectid = found.objectid + 1;

	scratch_leaf = btrfs_clone_extent_buffer(path->nodes[0]);
	if (!scratch_leaf) {
		ret = -ENOMEM;
		mutex_unlock(&fs_info->qgroup_rescan_lock);
		goto out;
	}
	slot = path->slots[0];
	btrfs_release_path(path);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	for (; slot < btrfs_header_nritems(scratch_leaf); ++slot) {
		btrfs_item_key_to_cpu(scratch_leaf, &found, slot);
		if (found.type != BTRFS_EXTENT_ITEM_KEY &&
		    found.type != BTRFS_METADATA_ITEM_KEY)
			continue;
		if (found.type == BTRFS_METADATA_ITEM_KEY)
			num_bytes = fs_info->nodesize;
		else
			num_bytes = found.offset;

		ret = btrfs_find_all_roots(NULL, fs_info, found.objectid, 0,
					   &roots, false);
		if (ret < 0)
			goto out;
		/* For rescan, just pass old_roots as NULL */
		ret = btrfs_qgroup_account_extent(trans, found.objectid,
						  num_bytes, NULL, roots);
		if (ret < 0)
			goto out;
	}
out:
	if (scratch_leaf)
		free_extent_buffer(scratch_leaf);

	if (done && !ret) {
		ret = 1;
		fs_info->qgroup_rescan_progress.objectid = (u64)-1;
	}
	return ret;
}