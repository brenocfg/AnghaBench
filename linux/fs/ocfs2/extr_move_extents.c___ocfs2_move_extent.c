#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_path {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  et_root_bh; int /*<<< orphan*/  et_ci; } ;
struct ocfs2_move_extents_context {int /*<<< orphan*/  dealloc; int /*<<< orphan*/  meta_ac; int /*<<< orphan*/  new_phys_cpos; TYPE_1__ et; struct inode* inode; } ;
struct ocfs2_extent_rec {int e_flags; int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  replace_rec ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_decrease_refcount (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ocfs2_duplicate_clusters_by_page (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (TYPE_1__*) ; 
 int ocfs2_search_extent_list (struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 int ocfs2_split_extent (int /*<<< orphan*/ *,TYPE_1__*,struct ocfs2_path*,int,struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int __ocfs2_move_extent(handle_t *handle,
			       struct ocfs2_move_extents_context *context,
			       u32 cpos, u32 len, u32 p_cpos, u32 new_p_cpos,
			       int ext_flags)
{
	int ret = 0, index;
	struct inode *inode = context->inode;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_extent_rec *rec, replace_rec;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_list *el;
	u64 ino = ocfs2_metadata_cache_owner(context->et.et_ci);
	u64 old_blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cpos);

	ret = ocfs2_duplicate_clusters_by_page(handle, inode, cpos,
					       p_cpos, new_p_cpos, len);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	memset(&replace_rec, 0, sizeof(replace_rec));
	replace_rec.e_cpos = cpu_to_le32(cpos);
	replace_rec.e_leaf_clusters = cpu_to_le16(len);
	replace_rec.e_blkno = cpu_to_le64(ocfs2_clusters_to_blocks(inode->i_sb,
								   new_p_cpos));

	path = ocfs2_new_path_from_et(&context->et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(INODE_CACHE(inode), path, cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	el = path_leaf_el(path);

	index = ocfs2_search_extent_list(el, cpos);
	if (index == -1) {
		ret = ocfs2_error(inode->i_sb,
				  "Inode %llu has an extent at cpos %u which can no longer be found\n",
				  (unsigned long long)ino, cpos);
		goto out;
	}

	rec = &el->l_recs[index];

	BUG_ON(ext_flags != rec->e_flags);
	/*
	 * after moving/defraging to new location, the extent is not going
	 * to be refcounted anymore.
	 */
	replace_rec.e_flags = ext_flags & ~OCFS2_EXT_REFCOUNTED;

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
				      context->et.et_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_split_extent(handle, &context->et, path, index,
				 &replace_rec, context->meta_ac,
				 &context->dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ocfs2_journal_dirty(handle, context->et.et_root_bh);

	context->new_phys_cpos = new_p_cpos;

	/*
	 * need I to append truncate log for old clusters?
	 */
	if (old_blkno) {
		if (ext_flags & OCFS2_EXT_REFCOUNTED)
			ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(osb->sb,
								 old_blkno),
					len, context->meta_ac,
					&context->dealloc, 1);
		else
			ret = ocfs2_truncate_log_append(osb, handle,
							old_blkno, len);
	}

	ocfs2_update_inode_fsync_trans(handle, inode, 0);
out:
	ocfs2_free_path(path);
	return ret;
}