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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_refcount; int /*<<< orphan*/  r_clusters; int /*<<< orphan*/  r_cpos; } ;
struct ocfs2_refcount_list {scalar_t__ rl_used; scalar_t__ rl_count; struct ocfs2_refcount_rec* rl_recs; } ;
struct ocfs2_refcount_block {struct ocfs2_refcount_list rf_records; int /*<<< orphan*/  rf_flags; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int OCFS2_REFCOUNT_TREE_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int le16_to_cpu (scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_refcount_rec*,struct ocfs2_refcount_rec*,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_adjust_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_refcount_rec*) ; 
 int ocfs2_expand_refcount_tree (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*) ; 
 int ocfs2_get_refcount_rec (struct ocfs2_caching_info*,struct buffer_head*,scalar_t__,int,int /*<<< orphan*/ *,int*,struct buffer_head**) ; 
 int ocfs2_journal_access_rb (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_refcount_rec_merge (struct ocfs2_refcount_block*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_insert_refcount_rec (unsigned long long,int,unsigned long long,int,int) ; 

__attribute__((used)) static int ocfs2_insert_refcount_rec(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_root_bh,
				     struct buffer_head *ref_leaf_bh,
				     struct ocfs2_refcount_rec *rec,
				     int index, int merge,
				     struct ocfs2_alloc_context *meta_ac)
{
	int ret;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_list *rf_list = &rb->rf_records;
	struct buffer_head *new_bh = NULL;

	BUG_ON(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL);

	if (rf_list->rl_used == rf_list->rl_count) {
		u64 cpos = le64_to_cpu(rec->r_cpos);
		u32 len = le32_to_cpu(rec->r_clusters);

		ret = ocfs2_expand_refcount_tree(handle, ci, ref_root_bh,
						 ref_leaf_bh, meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, NULL, &index,
					     &new_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ref_leaf_bh = new_bh;
		rb = (struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
		rf_list = &rb->rf_records;
	}

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (index < le16_to_cpu(rf_list->rl_used))
		memmove(&rf_list->rl_recs[index + 1],
			&rf_list->rl_recs[index],
			(le16_to_cpu(rf_list->rl_used) - index) *
			 sizeof(struct ocfs2_refcount_rec));

	trace_ocfs2_insert_refcount_rec(
		(unsigned long long)ref_leaf_bh->b_blocknr, index,
		(unsigned long long)le64_to_cpu(rec->r_cpos),
		le32_to_cpu(rec->r_clusters), le32_to_cpu(rec->r_refcount));

	rf_list->rl_recs[index] = *rec;

	le16_add_cpu(&rf_list->rl_used, 1);

	if (merge)
		ocfs2_refcount_rec_merge(rb, index);

	ocfs2_journal_dirty(handle, ref_leaf_bh);

	if (index == 0) {
		ret = ocfs2_adjust_refcount_rec(handle, ci,
						ref_root_bh,
						ref_leaf_bh, rec);
		if (ret)
			mlog_errno(ret);
	}
out:
	brelse(new_bh);
	return ret;
}