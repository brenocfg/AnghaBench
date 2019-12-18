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
typedef  size_t u16 ;
struct ocfs2_xattr_value_root {int dummy; } ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  dealloc; int /*<<< orphan*/ * meta_ac; int /*<<< orphan*/  handle; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct ocfs2_xattr_header {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_rm_xattr_bucket_para {int /*<<< orphan*/  ref_root_bh; int /*<<< orphan*/  ref_ci; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct ocfs2_xattr_header* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blocks_per_xattr_bucket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (int /*<<< orphan*/ *) ; 
 int ocfs2_get_xattr_tree_value_root (int /*<<< orphan*/ ,struct ocfs2_xattr_bucket*,size_t,struct ocfs2_xattr_value_root**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (int /*<<< orphan*/ *) ; 
 int ocfs2_lock_xattr_remove_allocators (struct inode*,struct ocfs2_xattr_value_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int ocfs2_remove_extent_credits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int ocfs2_xattr_bucket_value_truncate (struct inode*,struct ocfs2_xattr_bucket*,size_t,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 
 scalar_t__ ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 

__attribute__((used)) static int ocfs2_delete_xattr_in_bucket(struct inode *inode,
					struct ocfs2_xattr_bucket *bucket,
					void *para)
{
	int ret = 0, ref_credits;
	struct ocfs2_xattr_header *xh = bucket_xh(bucket);
	u16 i;
	struct ocfs2_xattr_entry *xe;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_xattr_set_ctxt ctxt = {NULL, NULL,};
	int credits = ocfs2_remove_extent_credits(osb->sb) +
		ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	struct ocfs2_xattr_value_root *xv;
	struct ocfs2_rm_xattr_bucket_para *args =
			(struct ocfs2_rm_xattr_bucket_para *)para;

	ocfs2_init_dealloc_ctxt(&ctxt.dealloc);

	for (i = 0; i < le16_to_cpu(xh->xh_count); i++) {
		xe = &xh->xh_entries[i];
		if (ocfs2_xattr_is_local(xe))
			continue;

		ret = ocfs2_get_xattr_tree_value_root(inode->i_sb, bucket,
						      i, &xv, NULL);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_lock_xattr_remove_allocators(inode, xv,
							 args->ref_ci,
							 args->ref_root_bh,
							 &ctxt.meta_ac,
							 &ref_credits);

		ctxt.handle = ocfs2_start_trans(osb, credits + ref_credits);
		if (IS_ERR(ctxt.handle)) {
			ret = PTR_ERR(ctxt.handle);
			mlog_errno(ret);
			break;
		}

		ret = ocfs2_xattr_bucket_value_truncate(inode, bucket,
							i, 0, &ctxt);

		ocfs2_commit_trans(osb, ctxt.handle);
		if (ctxt.meta_ac) {
			ocfs2_free_alloc_context(ctxt.meta_ac);
			ctxt.meta_ac = NULL;
		}
		if (ret) {
			mlog_errno(ret);
			break;
		}
	}

	if (ctxt.meta_ac)
		ocfs2_free_alloc_context(ctxt.meta_ac);
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &ctxt.dealloc);
	return ret;
}