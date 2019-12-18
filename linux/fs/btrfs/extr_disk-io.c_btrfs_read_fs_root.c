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
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; int /*<<< orphan*/  state; TYPE_1__ root_key; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_REF_COWS ; 
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_check_and_init_root_item (int /*<<< orphan*/ *) ; 
 struct btrfs_root* btrfs_read_tree_root (struct btrfs_root*,struct btrfs_key*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct btrfs_root *btrfs_read_fs_root(struct btrfs_root *tree_root,
				      struct btrfs_key *location)
{
	struct btrfs_root *root;

	root = btrfs_read_tree_root(tree_root, location);
	if (IS_ERR(root))
		return root;

	if (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) {
		set_bit(BTRFS_ROOT_REF_COWS, &root->state);
		btrfs_check_and_init_root_item(&root->root_item);
	}

	return root;
}