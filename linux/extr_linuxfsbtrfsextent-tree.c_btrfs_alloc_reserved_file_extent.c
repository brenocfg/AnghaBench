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
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ADD_DELAYED_EXTENT ; 
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int btrfs_add_delayed_data_ref (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_ref_tree_mod (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_alloc_reserved_file_extent(struct btrfs_trans_handle *trans,
				     struct btrfs_root *root, u64 owner,
				     u64 offset, u64 ram_bytes,
				     struct btrfs_key *ins)
{
	int ret;

	BUG_ON(root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	btrfs_ref_tree_mod(root, ins->objectid, ins->offset, 0,
			   root->root_key.objectid, owner, offset,
			   BTRFS_ADD_DELAYED_EXTENT);

	ret = btrfs_add_delayed_data_ref(trans, ins->objectid,
					 ins->offset, 0,
					 root->root_key.objectid, owner,
					 offset, ram_bytes,
					 BTRFS_ADD_DELAYED_EXTENT, NULL, NULL);
	return ret;
}