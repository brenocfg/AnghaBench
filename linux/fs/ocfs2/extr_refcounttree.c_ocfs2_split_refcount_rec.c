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
struct ocfs2_refcount_rec {scalar_t__ r_cpos; void* r_refcount; void* r_clusters; } ;
struct ocfs2_refcount_list {struct ocfs2_refcount_rec* rl_recs; int /*<<< orphan*/  rl_used; int /*<<< orphan*/  rl_count; } ;
struct ocfs2_refcount_block {struct ocfs2_refcount_list rf_records; void* rf_flags; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int OCFS2_REFCOUNT_TREE_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  le64_add_cpu (scalar_t__*,int) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct ocfs2_refcount_rec*,struct ocfs2_refcount_rec*,int) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_refcount_rec*,struct ocfs2_refcount_rec*,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_expand_refcount_tree (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*) ; 
 int ocfs2_get_refcount_rec (struct ocfs2_caching_info*,struct buffer_head*,scalar_t__,int,struct ocfs2_refcount_rec*,int*,struct buffer_head**) ; 
 int ocfs2_journal_access_rb (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_refcount_rec_merge (struct ocfs2_refcount_block*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_split_refcount_rec (scalar_t__,int,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_split_refcount_rec_insert (unsigned long long,int,unsigned long long,int,int) ; 

__attribute__((used)) static int ocfs2_split_refcount_rec(handle_t *handle,
				    struct ocfs2_caching_info *ci,
				    struct buffer_head *ref_root_bh,
				    struct buffer_head *ref_leaf_bh,
				    struct ocfs2_refcount_rec *split_rec,
				    int index, int merge,
				    struct ocfs2_alloc_context *meta_ac,
				    struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret, recs_need;
	u32 len;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_list *rf_list = &rb->rf_records;
	struct ocfs2_refcount_rec *orig_rec = &rf_list->rl_recs[index];
	struct ocfs2_refcount_rec *tail_rec = NULL;
	struct buffer_head *new_bh = NULL;

	BUG_ON(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL);

	trace_ocfs2_split_refcount_rec(le64_to_cpu(orig_rec->r_cpos),
		le32_to_cpu(orig_rec->r_clusters),
		le32_to_cpu(orig_rec->r_refcount),
		le64_to_cpu(split_rec->r_cpos),
		le32_to_cpu(split_rec->r_clusters),
		le32_to_cpu(split_rec->r_refcount));

	/*
	 * If we just need to split the header or tail clusters,
	 * no more recs are needed, just split is OK.
	 * Otherwise we at least need one new recs.
	 */
	if (!split_rec->r_refcount &&
	    (split_rec->r_cpos == orig_rec->r_cpos ||
	     le64_to_cpu(split_rec->r_cpos) +
	     le32_to_cpu(split_rec->r_clusters) ==
	     le64_to_cpu(orig_rec->r_cpos) + le32_to_cpu(orig_rec->r_clusters)))
		recs_need = 0;
	else
		recs_need = 1;

	/*
	 * We need one more rec if we split in the middle and the new rec have
	 * some refcount in it.
	 */
	if (split_rec->r_refcount &&
	    (split_rec->r_cpos != orig_rec->r_cpos &&
	     le64_to_cpu(split_rec->r_cpos) +
	     le32_to_cpu(split_rec->r_clusters) !=
	     le64_to_cpu(orig_rec->r_cpos) + le32_to_cpu(orig_rec->r_clusters)))
		recs_need++;

	/* If the leaf block don't have enough record, expand it. */
	if (le16_to_cpu(rf_list->rl_used) + recs_need >
					 le16_to_cpu(rf_list->rl_count)) {
		struct ocfs2_refcount_rec tmp_rec;
		u64 cpos = le64_to_cpu(orig_rec->r_cpos);
		len = le32_to_cpu(orig_rec->r_clusters);
		ret = ocfs2_expand_refcount_tree(handle, ci, ref_root_bh,
						 ref_leaf_bh, meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		/*
		 * We have to re-get it since now cpos may be moved to
		 * another leaf block.
		 */
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &tmp_rec, &index,
					     &new_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		ref_leaf_bh = new_bh;
		rb = (struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
		rf_list = &rb->rf_records;
		orig_rec = &rf_list->rl_recs[index];
	}

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * We have calculated out how many new records we need and store
	 * in recs_need, so spare enough space first by moving the records
	 * after "index" to the end.
	 */
	if (index != le16_to_cpu(rf_list->rl_used) - 1)
		memmove(&rf_list->rl_recs[index + 1 + recs_need],
			&rf_list->rl_recs[index + 1],
			(le16_to_cpu(rf_list->rl_used) - index - 1) *
			 sizeof(struct ocfs2_refcount_rec));

	len = (le64_to_cpu(orig_rec->r_cpos) +
	      le32_to_cpu(orig_rec->r_clusters)) -
	      (le64_to_cpu(split_rec->r_cpos) +
	      le32_to_cpu(split_rec->r_clusters));

	/*
	 * If we have "len", the we will split in the tail and move it
	 * to the end of the space we have just spared.
	 */
	if (len) {
		tail_rec = &rf_list->rl_recs[index + recs_need];

		memcpy(tail_rec, orig_rec, sizeof(struct ocfs2_refcount_rec));
		le64_add_cpu(&tail_rec->r_cpos,
			     le32_to_cpu(tail_rec->r_clusters) - len);
		tail_rec->r_clusters = cpu_to_le32(len);
	}

	/*
	 * If the split pos isn't the same as the original one, we need to
	 * split in the head.
	 *
	 * Note: We have the chance that split_rec.r_refcount = 0,
	 * recs_need = 0 and len > 0, which means we just cut the head from
	 * the orig_rec and in that case we have done some modification in
	 * orig_rec above, so the check for r_cpos is faked.
	 */
	if (split_rec->r_cpos != orig_rec->r_cpos && tail_rec != orig_rec) {
		len = le64_to_cpu(split_rec->r_cpos) -
		      le64_to_cpu(orig_rec->r_cpos);
		orig_rec->r_clusters = cpu_to_le32(len);
		index++;
	}

	le16_add_cpu(&rf_list->rl_used, recs_need);

	if (split_rec->r_refcount) {
		rf_list->rl_recs[index] = *split_rec;
		trace_ocfs2_split_refcount_rec_insert(
			(unsigned long long)ref_leaf_bh->b_blocknr, index,
			(unsigned long long)le64_to_cpu(split_rec->r_cpos),
			le32_to_cpu(split_rec->r_clusters),
			le32_to_cpu(split_rec->r_refcount));

		if (merge)
			ocfs2_refcount_rec_merge(rb, index);
	}

	ocfs2_journal_dirty(handle, ref_leaf_bh);

out:
	brelse(new_bh);
	return ret;
}