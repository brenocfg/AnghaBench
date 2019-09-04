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
typedef  int u32 ;
struct ocfs2_super {int s_clustersize_bits; int /*<<< orphan*/  sb; } ;
struct ocfs2_path {scalar_t__ p_tree_depth; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_rec {int e_flags; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_refcount_loc; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_calc_trunc_pos (struct inode*,struct ocfs2_extent_list*,struct ocfs2_extent_rec*,int,int*,int*,int*,scalar_t__*,int*) ; 
 int ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_cow_file_pos (struct inode*,struct buffer_head*,scalar_t__) ; 
 int ocfs2_find_cpos_for_left_leaf (int /*<<< orphan*/ ,struct ocfs2_path*,int*) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int) ; 
 int ocfs2_find_rec (struct ocfs2_extent_list*,int) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ ocfs2_is_refcount_inode (struct inode*) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 int /*<<< orphan*/  ocfs2_reinit_path (struct ocfs2_path*,int) ; 
 int ocfs2_remove_btree_range (struct inode*,struct ocfs2_extent_tree*,int,int,int,int,struct ocfs2_cached_dealloc_ctxt*,scalar_t__,int) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_truncate_cluster_pages (struct inode*,scalar_t__,scalar_t__) ; 
 int ocfs2_truncate_inline (struct inode*,struct buffer_head*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_zero_partial_clusters (struct inode*,scalar_t__,scalar_t__) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_remove_inode_range (unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocfs2_remove_inode_range(struct inode *inode,
			     struct buffer_head *di_bh, u64 byte_start,
			     u64 byte_len)
{
	int ret = 0, flags = 0, done = 0, i;
	u32 trunc_start, trunc_len, trunc_end, trunc_cpos, phys_cpos;
	u32 cluster_in_el;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_cached_dealloc_ctxt dealloc;
	struct address_space *mapping = inode->i_mapping;
	struct ocfs2_extent_tree et;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_list *el = NULL;
	struct ocfs2_extent_rec *rec = NULL;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	u64 blkno, refcount_loc = le64_to_cpu(di->i_refcount_loc);

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&dealloc);

	trace_ocfs2_remove_inode_range(
			(unsigned long long)OCFS2_I(inode)->ip_blkno,
			(unsigned long long)byte_start,
			(unsigned long long)byte_len);

	if (byte_len == 0)
		return 0;

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		ret = ocfs2_truncate_inline(inode, di_bh, byte_start,
					    byte_start + byte_len, 0);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
		/*
		 * There's no need to get fancy with the page cache
		 * truncate of an inline-data inode. We're talking
		 * about less than a page here, which will be cached
		 * in the dinode buffer anyway.
		 */
		unmap_mapping_range(mapping, 0, 0, 0);
		truncate_inode_pages(mapping, 0);
		goto out;
	}

	/*
	 * For reflinks, we may need to CoW 2 clusters which might be
	 * partially zero'd later, if hole's start and end offset were
	 * within one cluster(means is not exactly aligned to clustersize).
	 */

	if (ocfs2_is_refcount_inode(inode)) {
		ret = ocfs2_cow_file_pos(inode, di_bh, byte_start);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_cow_file_pos(inode, di_bh, byte_start + byte_len);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	trunc_start = ocfs2_clusters_for_bytes(osb->sb, byte_start);
	trunc_end = (byte_start + byte_len) >> osb->s_clustersize_bits;
	cluster_in_el = trunc_end;

	ret = ocfs2_zero_partial_clusters(inode, byte_start, byte_len);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	path = ocfs2_new_path_from_et(&et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	while (trunc_end > trunc_start) {

		ret = ocfs2_find_path(INODE_CACHE(inode), path,
				      cluster_in_el);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		el = path_leaf_el(path);

		i = ocfs2_find_rec(el, trunc_end);
		/*
		 * Need to go to previous extent block.
		 */
		if (i < 0) {
			if (path->p_tree_depth == 0)
				break;

			ret = ocfs2_find_cpos_for_left_leaf(inode->i_sb,
							    path,
							    &cluster_in_el);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			/*
			 * We've reached the leftmost extent block,
			 * it's safe to leave.
			 */
			if (cluster_in_el == 0)
				break;

			/*
			 * The 'pos' searched for previous extent block is
			 * always one cluster less than actual trunc_end.
			 */
			trunc_end = cluster_in_el + 1;

			ocfs2_reinit_path(path, 1);

			continue;

		} else
			rec = &el->l_recs[i];

		ocfs2_calc_trunc_pos(inode, el, rec, trunc_start, &trunc_cpos,
				     &trunc_len, &trunc_end, &blkno, &done);
		if (done)
			break;

		flags = rec->e_flags;
		phys_cpos = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

		ret = ocfs2_remove_btree_range(inode, &et, trunc_cpos,
					       phys_cpos, trunc_len, flags,
					       &dealloc, refcount_loc, false);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		cluster_in_el = trunc_end;

		ocfs2_reinit_path(path, 1);
	}

	ocfs2_truncate_cluster_pages(inode, byte_start, byte_len);

out:
	ocfs2_free_path(path);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &dealloc);

	return ret;
}