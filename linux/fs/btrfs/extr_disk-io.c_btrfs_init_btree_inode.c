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
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_ino; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; struct inode* btree_inode; } ;
struct TYPE_5__ {int track_uptodate; int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  location; int /*<<< orphan*/  root; TYPE_2__ io_tree; int /*<<< orphan*/  extent_tree; int /*<<< orphan*/  rb_node; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BTREE_INODE_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_DUMMY ; 
 int /*<<< orphan*/  IO_TREE_INODE_IO ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_aops ; 
 int /*<<< orphan*/  btree_extent_io_ops ; 
 int /*<<< orphan*/  btrfs_insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  extent_io_tree_init (struct btrfs_fs_info*,TYPE_2__*,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  extent_map_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static void btrfs_init_btree_inode(struct btrfs_fs_info *fs_info)
{
	struct inode *inode = fs_info->btree_inode;

	inode->i_ino = BTRFS_BTREE_INODE_OBJECTID;
	set_nlink(inode, 1);
	/*
	 * we set the i_size on the btree inode to the max possible int.
	 * the real end of the address space is determined by all of
	 * the devices in the system
	 */
	inode->i_size = OFFSET_MAX;
	inode->i_mapping->a_ops = &btree_aops;

	RB_CLEAR_NODE(&BTRFS_I(inode)->rb_node);
	extent_io_tree_init(fs_info, &BTRFS_I(inode)->io_tree,
			    IO_TREE_INODE_IO, inode);
	BTRFS_I(inode)->io_tree.track_uptodate = false;
	extent_map_tree_init(&BTRFS_I(inode)->extent_tree);

	BTRFS_I(inode)->io_tree.ops = &btree_extent_io_ops;

	BTRFS_I(inode)->root = fs_info->tree_root;
	memset(&BTRFS_I(inode)->location, 0, sizeof(struct btrfs_key));
	set_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runtime_flags);
	btrfs_insert_inode_hash(inode);
}