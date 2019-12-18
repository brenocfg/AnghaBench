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
typedef  int /*<<< orphan*/  u64 ;
struct ulist_node {int /*<<< orphan*/  aux; int /*<<< orphan*/  val; } ;
struct ulist_iterator {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct extent_changeset {int bytes_changed; int /*<<< orphan*/  range_changed; } ;
struct TYPE_6__ {TYPE_2__* root; int /*<<< orphan*/  io_tree; } ;
struct TYPE_4__ {int /*<<< orphan*/  objectid; } ;
struct TYPE_5__ {TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_QGROUP_RSV_DATA ; 
 int /*<<< orphan*/  EXTENT_QGROUP_RESERVED ; 
 int /*<<< orphan*/  ULIST_ITER_INIT (struct ulist_iterator*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_refroot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clear_record_extent_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_changeset*) ; 
 int /*<<< orphan*/  extent_changeset_init (struct extent_changeset*) ; 
 int /*<<< orphan*/  extent_changeset_release (struct extent_changeset*) ; 
 struct ulist_node* ulist_next (int /*<<< orphan*/ *,struct ulist_iterator*) ; 

void btrfs_qgroup_check_reserved_leak(struct inode *inode)
{
	struct extent_changeset changeset;
	struct ulist_node *unode;
	struct ulist_iterator iter;
	int ret;

	extent_changeset_init(&changeset);
	ret = clear_record_extent_bits(&BTRFS_I(inode)->io_tree, 0, (u64)-1,
			EXTENT_QGROUP_RESERVED, &changeset);

	WARN_ON(ret < 0);
	if (WARN_ON(changeset.bytes_changed)) {
		ULIST_ITER_INIT(&iter);
		while ((unode = ulist_next(&changeset.range_changed, &iter))) {
			btrfs_warn(BTRFS_I(inode)->root->fs_info,
				"leaking qgroup reserved space, ino: %lu, start: %llu, end: %llu",
				inode->i_ino, unode->val, unode->aux);
		}
		btrfs_qgroup_free_refroot(BTRFS_I(inode)->root->fs_info,
				BTRFS_I(inode)->root->root_key.objectid,
				changeset.bytes_changed, BTRFS_QGROUP_RSV_DATA);

	}
	extent_changeset_release(&changeset);
}