#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  moves; } ;
struct ocfs2_super {TYPE_1__ alloc_stats; TYPE_2__* local_alloc_bh; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_LA_EVENT_SLIDE ; 
 int /*<<< orphan*/  OCFS2_WINDOW_MOVE_CREDITS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dinode*) ; 
 struct ocfs2_dinode* kmemdup (struct ocfs2_dinode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_local_alloc (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ocfs2_local_alloc_new_window (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*) ; 
 int ocfs2_local_alloc_reserve_for_window (struct ocfs2_super*,struct ocfs2_alloc_context**,struct inode**,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_recalc_la_window (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_sync_local_to_main (struct ocfs2_super*,int /*<<< orphan*/ *,struct ocfs2_dinode*,struct inode*,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_local_alloc_slide_window(struct ocfs2_super *osb,
					  struct inode *local_alloc_inode)
{
	int status = 0;
	struct buffer_head *main_bm_bh = NULL;
	struct inode *main_bm_inode = NULL;
	handle_t *handle = NULL;
	struct ocfs2_dinode *alloc;
	struct ocfs2_dinode *alloc_copy = NULL;
	struct ocfs2_alloc_context *ac = NULL;

	ocfs2_recalc_la_window(osb, OCFS2_LA_EVENT_SLIDE);

	/* This will lock the main bitmap for us. */
	status = ocfs2_local_alloc_reserve_for_window(osb,
						      &ac,
						      &main_bm_inode,
						      &main_bm_bh);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	handle = ocfs2_start_trans(osb, OCFS2_WINDOW_MOVE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto bail;
	}

	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;

	/* We want to clear the local alloc before doing anything
	 * else, so that if we error later during this operation,
	 * local alloc shutdown won't try to double free main bitmap
	 * bits. Make a copy so the sync function knows which bits to
	 * free. */
	alloc_copy = kmemdup(alloc, osb->local_alloc_bh->b_size, GFP_NOFS);
	if (!alloc_copy) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(local_alloc_inode),
					 osb->local_alloc_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_clear_local_alloc(alloc);
	ocfs2_journal_dirty(handle, osb->local_alloc_bh);

	status = ocfs2_sync_local_to_main(osb, handle, alloc_copy,
					  main_bm_inode, main_bm_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_local_alloc_new_window(osb, handle, ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	atomic_inc(&osb->alloc_stats.moves);

bail:
	if (handle)
		ocfs2_commit_trans(osb, handle);

	brelse(main_bm_bh);

	iput(main_bm_inode);
	kfree(alloc_copy);

	if (ac)
		ocfs2_free_alloc_context(ac);

	if (status)
		mlog_errno(status);
	return status;
}