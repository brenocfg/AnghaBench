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
struct inode {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {struct inode* btree_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  WAIT_NONE ; 
 struct extent_buffer* btrfs_find_create_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  read_extent_buffer_pages (int /*<<< orphan*/ *,struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void readahead_tree_block(struct btrfs_fs_info *fs_info, u64 bytenr)
{
	struct extent_buffer *buf = NULL;
	struct inode *btree_inode = fs_info->btree_inode;

	buf = btrfs_find_create_tree_block(fs_info, bytenr);
	if (IS_ERR(buf))
		return;
	read_extent_buffer_pages(&BTRFS_I(btree_inode)->io_tree,
				 buf, WAIT_NONE, 0);
	free_extent_buffer(buf);
}