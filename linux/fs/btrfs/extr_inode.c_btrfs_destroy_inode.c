#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int nrpages; } ;
struct inode {TYPE_1__ i_data; int /*<<< orphan*/  i_dentry; int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_ordered_extent {int /*<<< orphan*/  len; int /*<<< orphan*/  file_offset; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_6__ {int reserved; int size; } ;
struct TYPE_7__ {int outstanding_extents; int delalloc_bytes; int new_delalloc_bytes; int csum_bytes; int defrag_bytes; TYPE_2__ block_rsv; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_drop_extent_cache (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_ordered_extent* btrfs_lookup_first_ordered_extent (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_qgroup_check_reserved_leak (struct inode*) ; 
 int /*<<< orphan*/  btrfs_remove_ordered_extent (struct inode*,struct btrfs_ordered_extent*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_tree_del (struct inode*) ; 

void btrfs_destroy_inode(struct inode *inode)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_ordered_extent *ordered;
	struct btrfs_root *root = BTRFS_I(inode)->root;

	WARN_ON(!hlist_empty(&inode->i_dentry));
	WARN_ON(inode->i_data.nrpages);
	WARN_ON(BTRFS_I(inode)->block_rsv.reserved);
	WARN_ON(BTRFS_I(inode)->block_rsv.size);
	WARN_ON(BTRFS_I(inode)->outstanding_extents);
	WARN_ON(BTRFS_I(inode)->delalloc_bytes);
	WARN_ON(BTRFS_I(inode)->new_delalloc_bytes);
	WARN_ON(BTRFS_I(inode)->csum_bytes);
	WARN_ON(BTRFS_I(inode)->defrag_bytes);

	/*
	 * This can happen where we create an inode, but somebody else also
	 * created the same inode and we need to destroy the one we already
	 * created.
	 */
	if (!root)
		return;

	while (1) {
		ordered = btrfs_lookup_first_ordered_extent(inode, (u64)-1);
		if (!ordered)
			break;
		else {
			btrfs_err(fs_info,
				  "found ordered extent %llu %llu on inode cleanup",
				  ordered->file_offset, ordered->len);
			btrfs_remove_ordered_extent(inode, ordered);
			btrfs_put_ordered_extent(ordered);
			btrfs_put_ordered_extent(ordered);
		}
	}
	btrfs_qgroup_check_reserved_leak(inode);
	inode_tree_del(inode);
	btrfs_drop_extent_cache(BTRFS_I(inode), 0, (u64)-1, 0);
}