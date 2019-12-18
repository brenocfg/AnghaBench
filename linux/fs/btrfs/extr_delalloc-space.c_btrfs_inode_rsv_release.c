#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_block_rsv {int dummy; } ;
struct btrfs_inode {TYPE_1__* root; struct btrfs_block_rsv block_rsv; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 scalar_t__ __btrfs_block_rsv_release (struct btrfs_fs_info*,struct btrfs_block_rsv*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_qgroup_convert_reserved_meta (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_meta_prealloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfs_inode_rsv_release(struct btrfs_inode *inode, bool qgroup_free)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	struct btrfs_block_rsv *block_rsv = &inode->block_rsv;
	u64 released = 0;
	u64 qgroup_to_release = 0;

	/*
	 * Since we statically set the block_rsv->size we just want to say we
	 * are releasing 0 bytes, and then we'll just get the reservation over
	 * the size free'd.
	 */
	released = __btrfs_block_rsv_release(fs_info, block_rsv, 0,
					     &qgroup_to_release);
	if (released > 0)
		trace_btrfs_space_reservation(fs_info, "delalloc",
					      btrfs_ino(inode), released, 0);
	if (qgroup_free)
		btrfs_qgroup_free_meta_prealloc(inode->root, qgroup_to_release);
	else
		btrfs_qgroup_convert_reserved_meta(inode->root,
						   qgroup_to_release);
}