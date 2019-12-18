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
struct btrfs_super_block {int /*<<< orphan*/  uuid_tree_generation; int /*<<< orphan*/  cache_generation; int /*<<< orphan*/  root_level; int /*<<< orphan*/  generation; int /*<<< orphan*/  root; int /*<<< orphan*/  chunk_root_level; int /*<<< orphan*/  chunk_root_generation; int /*<<< orphan*/  chunk_root; } ;
struct btrfs_root_item {int /*<<< orphan*/  generation; int /*<<< orphan*/  level; int /*<<< orphan*/  bytenr; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; TYPE_2__* tree_root; TYPE_1__* chunk_root; struct btrfs_super_block* super_copy; } ;
struct TYPE_4__ {struct btrfs_root_item root_item; } ;
struct TYPE_3__ {struct btrfs_root_item root_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_UPDATE_UUID_TREE_GEN ; 
 int /*<<< orphan*/  SPACE_CACHE ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_super_roots(struct btrfs_fs_info *fs_info)
{
	struct btrfs_root_item *root_item;
	struct btrfs_super_block *super;

	super = fs_info->super_copy;

	root_item = &fs_info->chunk_root->root_item;
	super->chunk_root = root_item->bytenr;
	super->chunk_root_generation = root_item->generation;
	super->chunk_root_level = root_item->level;

	root_item = &fs_info->tree_root->root_item;
	super->root = root_item->bytenr;
	super->generation = root_item->generation;
	super->root_level = root_item->level;
	if (btrfs_test_opt(fs_info, SPACE_CACHE))
		super->cache_generation = root_item->generation;
	if (test_bit(BTRFS_FS_UPDATE_UUID_TREE_GEN, &fs_info->flags))
		super->uuid_tree_generation = root_item->generation;
}