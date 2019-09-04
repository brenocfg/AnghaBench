#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btrfs_inode {TYPE_2__* root; } ;
struct btrfs_fs_info {TYPE_1__* delayed_root; int /*<<< orphan*/  flags; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {struct btrfs_fs_info* fs_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DELAYED_NODE_DEL_IREF ; 
 int /*<<< orphan*/  BTRFS_FS_LOG_RECOVERING ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct btrfs_delayed_node*) ; 
 int PTR_ERR (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct btrfs_delayed_node* btrfs_get_or_create_delayed_node (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_delayed_delete_inode_ref(struct btrfs_inode *inode)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	struct btrfs_delayed_node *delayed_node;

	/*
	 * we don't do delayed inode updates during log recovery because it
	 * leads to enospc problems.  This means we also can't do
	 * delayed inode refs
	 */
	if (test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags))
		return -EAGAIN;

	delayed_node = btrfs_get_or_create_delayed_node(inode);
	if (IS_ERR(delayed_node))
		return PTR_ERR(delayed_node);

	/*
	 * We don't reserve space for inode ref deletion is because:
	 * - We ONLY do async inode ref deletion for the inode who has only
	 *   one link(i_nlink == 1), it means there is only one inode ref.
	 *   And in most case, the inode ref and the inode item are in the
	 *   same leaf, and we will deal with them at the same time.
	 *   Since we are sure we will reserve the space for the inode item,
	 *   it is unnecessary to reserve space for inode ref deletion.
	 * - If the inode ref and the inode item are not in the same leaf,
	 *   We also needn't worry about enospc problem, because we reserve
	 *   much more space for the inode update than it needs.
	 * - At the worst, we can steal some space from the global reservation.
	 *   It is very rare.
	 */
	mutex_lock(&delayed_node->mutex);
	if (test_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags))
		goto release_node;

	set_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags);
	delayed_node->count++;
	atomic_inc(&fs_info->delayed_root->items);
release_node:
	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	return 0;
}