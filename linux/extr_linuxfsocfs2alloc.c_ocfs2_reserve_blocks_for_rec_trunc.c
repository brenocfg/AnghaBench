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
 int ENOSPC ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_extend_meta_needed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_num_free_extents (struct ocfs2_extent_tree*) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 scalar_t__ ocfs2_sparse_alloc (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_reserve_blocks_for_rec_trunc(struct inode *inode,
					      struct ocfs2_extent_tree *et,
					      u32 extents_to_split,
					      struct ocfs2_alloc_context **ac,
					      int extra_blocks)
{
	int ret = 0, num_free_extents;
	unsigned int max_recs_needed = 2 * extents_to_split;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	*ac = NULL;

	num_free_extents = ocfs2_num_free_extents(et);
	if (num_free_extents < 0) {
		ret = num_free_extents;
		mlog_errno(ret);
		goto out;
	}

	if (!num_free_extents ||
	    (ocfs2_sparse_alloc(osb) && num_free_extents < max_recs_needed))
		extra_blocks += ocfs2_extend_meta_needed(et->et_root_el);

	if (extra_blocks) {
		ret = ocfs2_reserve_new_metadata_blocks(osb, extra_blocks, ac);
		if (ret < 0) {
			if (ret != -ENOSPC)
				mlog_errno(ret);
		}
	}

out:
	if (ret) {
		if (*ac) {
			ocfs2_free_alloc_context(*ac);
			*ac = NULL;
		}
	}

	return ret;
}