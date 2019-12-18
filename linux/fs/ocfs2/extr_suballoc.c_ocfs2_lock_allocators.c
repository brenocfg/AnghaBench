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
typedef  int u32 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_el; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_num_free_extents (struct ocfs2_extent_tree*) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_metadata (struct ocfs2_super*,int /*<<< orphan*/ ,struct ocfs2_alloc_context**) ; 
 scalar_t__ ocfs2_sparse_alloc (struct ocfs2_super*) ; 

int ocfs2_lock_allocators(struct inode *inode,
			  struct ocfs2_extent_tree *et,
			  u32 clusters_to_add, u32 extents_to_split,
			  struct ocfs2_alloc_context **data_ac,
			  struct ocfs2_alloc_context **meta_ac)
{
	int ret = 0, num_free_extents;
	unsigned int max_recs_needed = clusters_to_add + 2 * extents_to_split;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	*meta_ac = NULL;
	if (data_ac)
		*data_ac = NULL;

	BUG_ON(clusters_to_add != 0 && data_ac == NULL);

	num_free_extents = ocfs2_num_free_extents(et);
	if (num_free_extents < 0) {
		ret = num_free_extents;
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Sparse allocation file systems need to be more conservative
	 * with reserving room for expansion - the actual allocation
	 * happens while we've got a journal handle open so re-taking
	 * a cluster lock (because we ran out of room for another
	 * extent) will violate ordering rules.
	 *
	 * Most of the time we'll only be seeing this 1 cluster at a time
	 * anyway.
	 *
	 * Always lock for any unwritten extents - we might want to
	 * add blocks during a split.
	 */
	if (!num_free_extents ||
	    (ocfs2_sparse_alloc(osb) && num_free_extents < max_recs_needed)) {
		ret = ocfs2_reserve_new_metadata(osb, et->et_root_el, meta_ac);
		if (ret < 0) {
			if (ret != -ENOSPC)
				mlog_errno(ret);
			goto out;
		}
	}

	if (clusters_to_add == 0)
		goto out;

	ret = ocfs2_reserve_clusters(osb, clusters_to_add, data_ac);
	if (ret < 0) {
		if (ret != -ENOSPC)
			mlog_errno(ret);
		goto out;
	}

out:
	if (ret) {
		if (*meta_ac) {
			ocfs2_free_alloc_context(*meta_ac);
			*meta_ac = NULL;
		}

		/*
		 * We cannot have an error and a non null *data_ac.
		 */
	}

	return ret;
}