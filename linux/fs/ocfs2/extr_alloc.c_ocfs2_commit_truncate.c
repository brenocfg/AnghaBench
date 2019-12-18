#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_refcount_tree {int dummy; } ;
struct ocfs2_path {int /*<<< orphan*/  p_tree_depth; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_rec {int e_flags; scalar_t__ e_int_clusters; int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {scalar_t__ l_tree_depth; struct ocfs2_extent_rec* l_recs; scalar_t__ l_next_free_rec; } ;
struct TYPE_4__ {struct ocfs2_extent_list i_list; } ;
struct ocfs2_dinode {TYPE_1__ id2; int /*<<< orphan*/  i_refcount_loc; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_6__ {scalar_t__ ip_clusters; scalar_t__ ip_blkno; } ;
struct TYPE_5__ {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_EXT_REFCOUNTED ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_extent_map_trunc (struct inode*,scalar_t__) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_journal_access_di ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,scalar_t__,int,struct ocfs2_refcount_tree**,int /*<<< orphan*/ *) ; 
 struct ocfs2_path* ocfs2_new_path (struct buffer_head*,struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_reinit_path (struct ocfs2_path*,int) ; 
 int ocfs2_remove_btree_range (struct inode*,struct ocfs2_extent_tree*,scalar_t__,scalar_t__,scalar_t__,int,struct ocfs2_cached_dealloc_ctxt*,scalar_t__,int) ; 
 int ocfs2_remove_rightmost_empty_extent (struct ocfs2_super*,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 TYPE_2__* path_leaf_bh (struct ocfs2_path*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_commit_truncate (unsigned long long,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int ocfs2_commit_truncate(struct ocfs2_super *osb,
			  struct inode *inode,
			  struct buffer_head *di_bh)
{
	int status = 0, i, flags = 0;
	u32 new_highest_cpos, range, trunc_cpos, trunc_len, phys_cpos, coff;
	u64 blkno = 0;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_path *path = NULL;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_extent_list *root_el = &(di->id2.i_list);
	u64 refcount_loc = le64_to_cpu(di->i_refcount_loc);
	struct ocfs2_extent_tree et;
	struct ocfs2_cached_dealloc_ctxt dealloc;
	struct ocfs2_refcount_tree *ref_tree = NULL;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_dealloc_ctxt(&dealloc);

	new_highest_cpos = ocfs2_clusters_for_bytes(osb->sb,
						     i_size_read(inode));

	path = ocfs2_new_path(di_bh, &di->id2.i_list,
			      ocfs2_journal_access_di);
	if (!path) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	ocfs2_extent_map_trunc(inode, new_highest_cpos);

start:
	/*
	 * Check that we still have allocation to delete.
	 */
	if (OCFS2_I(inode)->ip_clusters == 0) {
		status = 0;
		goto bail;
	}

	/*
	 * Truncate always works against the rightmost tree branch.
	 */
	status = ocfs2_find_path(INODE_CACHE(inode), path, UINT_MAX);
	if (status) {
		mlog_errno(status);
		goto bail;
	}

	trace_ocfs2_commit_truncate(
		(unsigned long long)OCFS2_I(inode)->ip_blkno,
		new_highest_cpos,
		OCFS2_I(inode)->ip_clusters,
		path->p_tree_depth);

	/*
	 * By now, el will point to the extent list on the bottom most
	 * portion of this tree. Only the tail record is considered in
	 * each pass.
	 *
	 * We handle the following cases, in order:
	 * - empty extent: delete the remaining branch
	 * - remove the entire record
	 * - remove a partial record
	 * - no record needs to be removed (truncate has completed)
	 */
	el = path_leaf_el(path);
	if (le16_to_cpu(el->l_next_free_rec) == 0) {
		ocfs2_error(inode->i_sb,
			    "Inode %llu has empty extent block at %llu\n",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno,
			    (unsigned long long)path_leaf_bh(path)->b_blocknr);
		status = -EROFS;
		goto bail;
	}

	i = le16_to_cpu(el->l_next_free_rec) - 1;
	rec = &el->l_recs[i];
	flags = rec->e_flags;
	range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);

	if (i == 0 && ocfs2_is_empty_extent(rec)) {
		/*
		 * Lower levels depend on this never happening, but it's best
		 * to check it up here before changing the tree.
		*/
		if (root_el->l_tree_depth && rec->e_int_clusters == 0) {
			mlog(ML_ERROR, "Inode %lu has an empty "
				    "extent record, depth %u\n", inode->i_ino,
				    le16_to_cpu(root_el->l_tree_depth));
			status = ocfs2_remove_rightmost_empty_extent(osb,
					&et, path, &dealloc);
			if (status) {
				mlog_errno(status);
				goto bail;
			}

			ocfs2_reinit_path(path, 1);
			goto start;
		} else {
			trunc_cpos = le32_to_cpu(rec->e_cpos);
			trunc_len = 0;
			blkno = 0;
		}
	} else if (le32_to_cpu(rec->e_cpos) >= new_highest_cpos) {
		/*
		 * Truncate entire record.
		 */
		trunc_cpos = le32_to_cpu(rec->e_cpos);
		trunc_len = ocfs2_rec_clusters(el, rec);
		blkno = le64_to_cpu(rec->e_blkno);
	} else if (range > new_highest_cpos) {
		/*
		 * Partial truncate. it also should be
		 * the last truncate we're doing.
		 */
		trunc_cpos = new_highest_cpos;
		trunc_len = range - new_highest_cpos;
		coff = new_highest_cpos - le32_to_cpu(rec->e_cpos);
		blkno = le64_to_cpu(rec->e_blkno) +
				ocfs2_clusters_to_blocks(inode->i_sb, coff);
	} else {
		/*
		 * Truncate completed, leave happily.
		 */
		status = 0;
		goto bail;
	}

	phys_cpos = ocfs2_blocks_to_clusters(inode->i_sb, blkno);

	if ((flags & OCFS2_EXT_REFCOUNTED) && trunc_len && !ref_tree) {
		status = ocfs2_lock_refcount_tree(osb, refcount_loc, 1,
				&ref_tree, NULL);
		if (status) {
			mlog_errno(status);
			goto bail;
		}
	}

	status = ocfs2_remove_btree_range(inode, &et, trunc_cpos,
					  phys_cpos, trunc_len, flags, &dealloc,
					  refcount_loc, true);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_reinit_path(path, 1);

	/*
	 * The check above will catch the case where we've truncated
	 * away all allocation.
	 */
	goto start;

bail:
	if (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	ocfs2_schedule_truncate_log_flush(osb, 1);

	ocfs2_run_deallocs(osb, &dealloc);

	ocfs2_free_path(path);

	return status;
}