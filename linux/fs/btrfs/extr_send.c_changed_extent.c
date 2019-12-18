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
struct send_ctx {scalar_t__ cur_ino; TYPE_1__* cmp_key; int /*<<< orphan*/  left_path; int /*<<< orphan*/  cur_inode_deleted; int /*<<< orphan*/  cur_inode_new_gen; } ;
typedef  enum btrfs_compare_tree_result { ____Placeholder_btrfs_compare_tree_result } btrfs_compare_tree_result ;
struct TYPE_2__ {scalar_t__ objectid; } ;

/* Variables and functions */
 int BTRFS_COMPARE_TREE_DELETED ; 
 int process_extent (struct send_ctx*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int changed_extent(struct send_ctx *sctx,
			  enum btrfs_compare_tree_result result)
{
	int ret = 0;

	/*
	 * We have found an extent item that changed without the inode item
	 * having changed. This can happen either after relocation (where the
	 * disk_bytenr of an extent item is replaced at
	 * relocation.c:replace_file_extents()) or after deduplication into a
	 * file in both the parent and send snapshots (where an extent item can
	 * get modified or replaced with a new one). Note that deduplication
	 * updates the inode item, but it only changes the iversion (sequence
	 * field in the inode item) of the inode, so if a file is deduplicated
	 * the same amount of times in both the parent and send snapshots, its
	 * iversion becames the same in both snapshots, whence the inode item is
	 * the same on both snapshots.
	 */
	if (sctx->cur_ino != sctx->cmp_key->objectid)
		return 0;

	if (!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted) {
		if (result != BTRFS_COMPARE_TREE_DELETED)
			ret = process_extent(sctx, sctx->left_path,
					sctx->cmp_key);
	}

	return ret;
}