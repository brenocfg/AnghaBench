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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int e_flags; int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (struct super_block*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 int ocfs2_search_extent_list (struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 int ocfs2_split_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,int,struct ocfs2_extent_rec*,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

int ocfs2_change_extent_flag(handle_t *handle,
			     struct ocfs2_extent_tree *et,
			     u32 cpos, u32 len, u32 phys,
			     struct ocfs2_alloc_context *meta_ac,
			     struct ocfs2_cached_dealloc_ctxt *dealloc,
			     int new_flags, int clear_flags)
{
	int ret, index;
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	u64 start_blkno = ocfs2_clusters_to_blocks(sb, phys);
	struct ocfs2_extent_rec split_rec;
	struct ocfs2_path *left_path = NULL;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	left_path = ocfs2_new_path_from_et(et);
	if (!left_path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(et->et_ci, left_path, cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	el = path_leaf_el(left_path);

	index = ocfs2_search_extent_list(el, cpos);
	if (index == -1) {
		ocfs2_error(sb,
			    "Owner %llu has an extent at cpos %u which can no longer be found\n",
			    (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
			    cpos);
		ret = -EROFS;
		goto out;
	}

	ret = -EIO;
	rec = &el->l_recs[index];
	if (new_flags && (rec->e_flags & new_flags)) {
		mlog(ML_ERROR, "Owner %llu tried to set %d flags on an "
		     "extent that already had them\n",
		     (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
		     new_flags);
		goto out;
	}

	if (clear_flags && !(rec->e_flags & clear_flags)) {
		mlog(ML_ERROR, "Owner %llu tried to clear %d flags on an "
		     "extent that didn't have them\n",
		     (unsigned long long)ocfs2_metadata_cache_owner(et->et_ci),
		     clear_flags);
		goto out;
	}

	memset(&split_rec, 0, sizeof(struct ocfs2_extent_rec));
	split_rec.e_cpos = cpu_to_le32(cpos);
	split_rec.e_leaf_clusters = cpu_to_le16(len);
	split_rec.e_blkno = cpu_to_le64(start_blkno);
	split_rec.e_flags = rec->e_flags;
	if (new_flags)
		split_rec.e_flags |= new_flags;
	if (clear_flags)
		split_rec.e_flags &= ~clear_flags;

	ret = ocfs2_split_extent(handle, et, left_path,
				 index, &split_rec, meta_ac,
				 dealloc);
	if (ret)
		mlog_errno(ret);

out:
	ocfs2_free_path(left_path);
	return ret;

}