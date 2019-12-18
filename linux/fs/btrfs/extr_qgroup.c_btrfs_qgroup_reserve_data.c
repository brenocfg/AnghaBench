#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ulist_node {int /*<<< orphan*/  aux; int /*<<< orphan*/  val; } ;
struct ulist_iterator {int dummy; } ;
struct inode {int dummy; } ;
struct extent_changeset {scalar_t__ bytes_changed; int /*<<< orphan*/  range_changed; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; TYPE_2__* fs_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  io_tree; struct btrfs_root* root; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_QGROUP_RSV_DATA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_QGROUP_RESERVED ; 
 int /*<<< orphan*/  QGROUP_RESERVE ; 
 int /*<<< orphan*/  ULIST_ITER_INIT (struct ulist_iterator*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_refroot (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct extent_changeset* extent_changeset_alloc () ; 
 int /*<<< orphan*/  extent_changeset_release (struct extent_changeset*) ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int qgroup_reserve (struct btrfs_root*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int set_record_extent_bits (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct extent_changeset*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_qgroup_reserve_data (struct inode*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ulist_node* ulist_next (int /*<<< orphan*/ *,struct ulist_iterator*) ; 

int btrfs_qgroup_reserve_data(struct inode *inode,
			struct extent_changeset **reserved_ret, u64 start,
			u64 len)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct ulist_node *unode;
	struct ulist_iterator uiter;
	struct extent_changeset *reserved;
	u64 orig_reserved;
	u64 to_reserve;
	int ret;

	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &root->fs_info->flags) ||
	    !is_fstree(root->root_key.objectid) || len == 0)
		return 0;

	/* @reserved parameter is mandatory for qgroup */
	if (WARN_ON(!reserved_ret))
		return -EINVAL;
	if (!*reserved_ret) {
		*reserved_ret = extent_changeset_alloc();
		if (!*reserved_ret)
			return -ENOMEM;
	}
	reserved = *reserved_ret;
	/* Record already reserved space */
	orig_reserved = reserved->bytes_changed;
	ret = set_record_extent_bits(&BTRFS_I(inode)->io_tree, start,
			start + len -1, EXTENT_QGROUP_RESERVED, reserved);

	/* Newly reserved space */
	to_reserve = reserved->bytes_changed - orig_reserved;
	trace_btrfs_qgroup_reserve_data(inode, start, len,
					to_reserve, QGROUP_RESERVE);
	if (ret < 0)
		goto cleanup;
	ret = qgroup_reserve(root, to_reserve, true, BTRFS_QGROUP_RSV_DATA);
	if (ret < 0)
		goto cleanup;

	return ret;

cleanup:
	/* cleanup *ALL* already reserved ranges */
	ULIST_ITER_INIT(&uiter);
	while ((unode = ulist_next(&reserved->range_changed, &uiter)))
		clear_extent_bit(&BTRFS_I(inode)->io_tree, unode->val,
				 unode->aux, EXTENT_QGROUP_RESERVED, 0, 0, NULL);
	/* Also free data bytes of already reserved one */
	btrfs_qgroup_free_refroot(root->fs_info, root->root_key.objectid,
				  orig_reserved, BTRFS_QGROUP_RSV_DATA);
	extent_changeset_release(reserved);
	return ret;
}