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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DROP_DELAYED_REF ; 
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  add_pinned_bytes (struct btrfs_fs_info*,scalar_t__,int,scalar_t__) ; 
 int btrfs_add_delayed_data_ref (struct btrfs_trans_handle*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int btrfs_add_delayed_tree_ref (struct btrfs_trans_handle*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_pin_extent (struct btrfs_fs_info*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_ref_tree_mod (struct btrfs_root*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int btrfs_free_extent(struct btrfs_trans_handle *trans,
		      struct btrfs_root *root,
		      u64 bytenr, u64 num_bytes, u64 parent, u64 root_objectid,
		      u64 owner, u64 offset)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int old_ref_mod, new_ref_mod;
	int ret;

	if (btrfs_is_testing(fs_info))
		return 0;

	if (root_objectid != BTRFS_TREE_LOG_OBJECTID)
		btrfs_ref_tree_mod(root, bytenr, num_bytes, parent,
				   root_objectid, owner, offset,
				   BTRFS_DROP_DELAYED_REF);

	/*
	 * tree log blocks never actually go into the extent allocation
	 * tree, just update pinning info and exit early.
	 */
	if (root_objectid == BTRFS_TREE_LOG_OBJECTID) {
		WARN_ON(owner >= BTRFS_FIRST_FREE_OBJECTID);
		/* unlocks the pinned mutex */
		btrfs_pin_extent(fs_info, bytenr, num_bytes, 1);
		old_ref_mod = new_ref_mod = 0;
		ret = 0;
	} else if (owner < BTRFS_FIRST_FREE_OBJECTID) {
		ret = btrfs_add_delayed_tree_ref(trans, bytenr,
						 num_bytes, parent,
						 root_objectid, (int)owner,
						 BTRFS_DROP_DELAYED_REF, NULL,
						 &old_ref_mod, &new_ref_mod);
	} else {
		ret = btrfs_add_delayed_data_ref(trans, bytenr,
						 num_bytes, parent,
						 root_objectid, owner, offset,
						 0, BTRFS_DROP_DELAYED_REF,
						 &old_ref_mod, &new_ref_mod);
	}

	if (ret == 0 && old_ref_mod >= 0 && new_ref_mod < 0) {
		bool metadata = owner < BTRFS_FIRST_FREE_OBJECTID;

		add_pinned_bytes(fs_info, num_bytes, metadata, root_objectid);
	}

	return ret;
}