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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; TYPE_1__ root_key; } ;
struct btrfs_ref {int /*<<< orphan*/  member_0; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ADD_DELAYED_EXTENT ; 
 int /*<<< orphan*/  BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int btrfs_add_delayed_data_ref (struct btrfs_trans_handle*,struct btrfs_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_init_data_ref (struct btrfs_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_generic_ref (struct btrfs_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_ref_tree_mod (int /*<<< orphan*/ ,struct btrfs_ref*) ; 

int btrfs_alloc_reserved_file_extent(struct btrfs_trans_handle *trans,
				     struct btrfs_root *root, u64 owner,
				     u64 offset, u64 ram_bytes,
				     struct btrfs_key *ins)
{
	struct btrfs_ref generic_ref = { 0 };
	int ret;

	BUG_ON(root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	btrfs_init_generic_ref(&generic_ref, BTRFS_ADD_DELAYED_EXTENT,
			       ins->objectid, ins->offset, 0);
	btrfs_init_data_ref(&generic_ref, root->root_key.objectid, owner, offset);
	btrfs_ref_tree_mod(root->fs_info, &generic_ref);
	ret = btrfs_add_delayed_data_ref(trans, &generic_ref,
					 ram_bytes, NULL, NULL);
	return ret;
}