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
typedef  scalar_t__ u64 ;
struct clone_root {scalar_t__ root; scalar_t__ ino; scalar_t__ offset; int /*<<< orphan*/  found_refs; } ;
struct backref_ctx {scalar_t__ cur_objectid; scalar_t__ cur_offset; int found_itself; scalar_t__ extent_len; int /*<<< orphan*/  found; TYPE_1__* sctx; } ;
struct TYPE_2__ {scalar_t__ send_root; int /*<<< orphan*/  clone_roots_cnt; int /*<<< orphan*/  clone_roots; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clone_root_cmp_bsearch ; 
 struct clone_root* bsearch (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __iterate_backrefs(u64 ino, u64 offset, u64 root, void *ctx_)
{
	struct backref_ctx *bctx = ctx_;
	struct clone_root *found;

	/* First check if the root is in the list of accepted clone sources */
	found = bsearch((void *)(uintptr_t)root, bctx->sctx->clone_roots,
			bctx->sctx->clone_roots_cnt,
			sizeof(struct clone_root),
			__clone_root_cmp_bsearch);
	if (!found)
		return 0;

	if (found->root == bctx->sctx->send_root &&
	    ino == bctx->cur_objectid &&
	    offset == bctx->cur_offset) {
		bctx->found_itself = 1;
	}

	/*
	 * Make sure we don't consider clones from send_root that are
	 * behind the current inode/offset.
	 */
	if (found->root == bctx->sctx->send_root) {
		/*
		 * TODO for the moment we don't accept clones from the inode
		 * that is currently send. We may change this when
		 * BTRFS_IOC_CLONE_RANGE supports cloning from and to the same
		 * file.
		 */
		if (ino >= bctx->cur_objectid)
			return 0;
	}

	bctx->found++;
	found->found_refs++;
	if (ino < found->ino) {
		found->ino = ino;
		found->offset = offset;
	} else if (found->ino == ino) {
		/*
		 * same extent found more then once in the same file.
		 */
		if (found->offset > offset + bctx->extent_len)
			found->offset = offset;
	}

	return 0;
}