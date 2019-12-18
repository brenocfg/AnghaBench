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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int nr_delalloc_inodes; int /*<<< orphan*/  delalloc_lock; int /*<<< orphan*/  delalloc_root; int /*<<< orphan*/  delalloc_inodes; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delalloc_root_lock; int /*<<< orphan*/  delalloc_roots; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  delalloc_inodes; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_IN_DELALLOC_LIST ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_add_delalloc_inodes(struct btrfs_root *root,
				      struct inode *inode)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

	spin_lock(&root->delalloc_lock);
	if (list_empty(&BTRFS_I(inode)->delalloc_inodes)) {
		list_add_tail(&BTRFS_I(inode)->delalloc_inodes,
			      &root->delalloc_inodes);
		set_bit(BTRFS_INODE_IN_DELALLOC_LIST,
			&BTRFS_I(inode)->runtime_flags);
		root->nr_delalloc_inodes++;
		if (root->nr_delalloc_inodes == 1) {
			spin_lock(&fs_info->delalloc_root_lock);
			BUG_ON(!list_empty(&root->delalloc_root));
			list_add_tail(&root->delalloc_root,
				      &fs_info->delalloc_roots);
			spin_unlock(&fs_info->delalloc_root_lock);
		}
	}
	spin_unlock(&root->delalloc_lock);
}