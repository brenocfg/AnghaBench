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
struct send_ctx {scalar_t__ cur_ino; int /*<<< orphan*/  cur_inode_deleted; int /*<<< orphan*/  cur_inode_new_gen; TYPE_1__* cmp_key; } ;
typedef  enum btrfs_compare_tree_result { ____Placeholder_btrfs_compare_tree_result } btrfs_compare_tree_result ;
struct TYPE_2__ {scalar_t__ objectid; } ;

/* Variables and functions */
 int BTRFS_COMPARE_TREE_CHANGED ; 
 int BTRFS_COMPARE_TREE_DELETED ; 
 int BTRFS_COMPARE_TREE_NEW ; 
 int EIO ; 
 int /*<<< orphan*/  inconsistent_snapshot_error (struct send_ctx*,int,char*) ; 
 int process_changed_xattr (struct send_ctx*) ; 
 int process_deleted_xattr (struct send_ctx*) ; 
 int process_new_xattr (struct send_ctx*) ; 

__attribute__((used)) static int changed_xattr(struct send_ctx *sctx,
			 enum btrfs_compare_tree_result result)
{
	int ret = 0;

	if (sctx->cur_ino != sctx->cmp_key->objectid) {
		inconsistent_snapshot_error(sctx, result, "xattr");
		return -EIO;
	}

	if (!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted) {
		if (result == BTRFS_COMPARE_TREE_NEW)
			ret = process_new_xattr(sctx);
		else if (result == BTRFS_COMPARE_TREE_DELETED)
			ret = process_deleted_xattr(sctx);
		else if (result == BTRFS_COMPARE_TREE_CHANGED)
			ret = process_changed_xattr(sctx);
	}

	return ret;
}