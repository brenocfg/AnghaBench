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
struct send_ctx {int flags; scalar_t__ parent_root; int /*<<< orphan*/  send_root; } ;

/* Variables and functions */
 int BTRFS_SEND_FLAG_OMIT_STREAM_HEADER ; 
 int btrfs_compare_trees (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct send_ctx*) ; 
 int /*<<< orphan*/  changed_cb ; 
 int finish_inode_if_needed (struct send_ctx*,int) ; 
 int /*<<< orphan*/  free_recorded_refs (struct send_ctx*) ; 
 int full_send_tree (struct send_ctx*) ; 
 int send_header (struct send_ctx*) ; 
 int send_subvol_begin (struct send_ctx*) ; 

__attribute__((used)) static int send_subvol(struct send_ctx *sctx)
{
	int ret;

	if (!(sctx->flags & BTRFS_SEND_FLAG_OMIT_STREAM_HEADER)) {
		ret = send_header(sctx);
		if (ret < 0)
			goto out;
	}

	ret = send_subvol_begin(sctx);
	if (ret < 0)
		goto out;

	if (sctx->parent_root) {
		ret = btrfs_compare_trees(sctx->send_root, sctx->parent_root,
				changed_cb, sctx);
		if (ret < 0)
			goto out;
		ret = finish_inode_if_needed(sctx, 1);
		if (ret < 0)
			goto out;
	} else {
		ret = full_send_tree(sctx);
		if (ret < 0)
			goto out;
	}

out:
	free_recorded_refs(sctx);
	return ret;
}