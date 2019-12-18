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
typedef  int u64 ;
struct btrfs_root_item {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int BTRFS_INODE_ROOT_ITEM_INIT ; 
 int /*<<< orphan*/  btrfs_set_root_flags (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_root_limit (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_flags (int /*<<< orphan*/ *,int) ; 
 int btrfs_stack_inode_flags (int /*<<< orphan*/ *) ; 

void btrfs_check_and_init_root_item(struct btrfs_root_item *root_item)
{
	u64 inode_flags = btrfs_stack_inode_flags(&root_item->inode);

	if (!(inode_flags & BTRFS_INODE_ROOT_ITEM_INIT)) {
		inode_flags |= BTRFS_INODE_ROOT_ITEM_INIT;
		btrfs_set_stack_inode_flags(&root_item->inode, inode_flags);
		btrfs_set_root_flags(root_item, 0);
		btrfs_set_root_limit(root_item, 0);
	}
}