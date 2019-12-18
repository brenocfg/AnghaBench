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
typedef  scalar_t__ u32 ;
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int EROFS ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,...) ; 
 int /*<<< orphan*/  ocfs2_et_extent_map_truncate (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 scalar_t__ ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_reinit_path (struct ocfs2_path*,int) ; 
 int ocfs2_search_extent_list (struct ocfs2_extent_list*,scalar_t__) ; 
 int ocfs2_split_tree (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,int,scalar_t__,struct ocfs2_alloc_context*) ; 
 int ocfs2_truncate_rec (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,int,struct ocfs2_cached_dealloc_ctxt*,scalar_t__,scalar_t__) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  trace_ocfs2_remove_extent (unsigned long long,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 

int ocfs2_remove_extent(handle_t *handle,
			struct ocfs2_extent_tree *et,
			u32 cpos, u32 len,
			struct ocfs2_alloc_context *meta_ac,
			struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret, index;
	u32 rec_range, trunc_range;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_extent_list *el;
	struct ocfs2_path *path = NULL;

	/*
	 * XXX: Why are we truncating to 0 instead of wherever this
	 * affects us?
	 */
	ocfs2_et_extent_map_truncate(et, 0);

	path = ocfs2_new_path_from_et(et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(et->et_ci, path, cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	el = path_leaf_el(path);
	index = ocfs2_search_extent_list(el, cpos);
	if (index == -1) {
		ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
			    "Owner %llu has an extent at cpos %u which can no longer be found\n",
			    (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
			    cpos);
		ret = -EROFS;
		goto out;
	}

	/*
	 * We have 3 cases of extent removal:
	 *   1) Range covers the entire extent rec
	 *   2) Range begins or ends on one edge of the extent rec
	 *   3) Range is in the middle of the extent rec (no shared edges)
	 *
	 * For case 1 we remove the extent rec and left rotate to
	 * fill the hole.
	 *
	 * For case 2 we just shrink the existing extent rec, with a
	 * tree update if the shrinking edge is also the edge of an
	 * extent block.
	 *
	 * For case 3 we do a right split to turn the extent rec into
	 * something case 2 can handle.
	 */
	rec = &el->l_recs[index];
	rec_range = le32_to_cpu(rec->e_cpos) + ocfs2_rec_clusters(el, rec);
	trunc_range = cpos + len;

	BUG_ON(cpos < le32_to_cpu(rec->e_cpos) || trunc_range > rec_range);

	trace_ocfs2_remove_extent(
		(unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
		cpos, len, index, le32_to_cpu(rec->e_cpos),
		ocfs2_rec_clusters(el, rec));

	if (le32_to_cpu(rec->e_cpos) == cpos || rec_range == trunc_range) {
		ret = ocfs2_truncate_rec(handle, et, path, index, dealloc,
					 cpos, len);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	} else {
		ret = ocfs2_split_tree(handle, et, path, index,
				       trunc_range, meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * The split could have manipulated the tree enough to
		 * move the record location, so we have to look for it again.
		 */
		ocfs2_reinit_path(path, 1);

		ret = ocfs2_find_path(et->et_ci, path, cpos);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		el = path_leaf_el(path);
		index = ocfs2_search_extent_list(el, cpos);
		if (index == -1) {
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu: split at cpos %u lost record\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
				    cpos);
			ret = -EROFS;
			goto out;
		}

		/*
		 * Double check our values here. If anything is fishy,
		 * it's easier to catch it at the top level.
		 */
		rec = &el->l_recs[index];
		rec_range = le32_to_cpu(rec->e_cpos) +
			ocfs2_rec_clusters(el, rec);
		if (rec_range != trunc_range) {
			ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
				    "Owner %llu: error after split at cpos %u trunc len %u, existing record is (%u,%u)\n",
				    (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
				    cpos, len, le32_to_cpu(rec->e_cpos),
				    ocfs2_rec_clusters(el, rec));
			ret = -EROFS;
			goto out;
		}

		ret = ocfs2_truncate_rec(handle, et, path, index, dealloc,
					 cpos, len);
		if (ret)
			mlog_errno(ret);
	}

out:
	ocfs2_free_path(path);
	return ret;
}