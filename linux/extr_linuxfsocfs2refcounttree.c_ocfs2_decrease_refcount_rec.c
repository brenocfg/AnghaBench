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
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_refcount; int /*<<< orphan*/  r_clusters; int /*<<< orphan*/  r_cpos; } ;
struct TYPE_2__ {int /*<<< orphan*/  rl_used; struct ocfs2_refcount_rec* rl_recs; } ;
struct ocfs2_refcount_block {TYPE_1__ rf_records; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_change_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int,int,int) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int ocfs2_remove_refcount_extent (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_split_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_refcount_rec*,int,int,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  trace_ocfs2_decrease_refcount_rec (unsigned long long,unsigned long long,unsigned int) ; 

__attribute__((used)) static int ocfs2_decrease_refcount_rec(handle_t *handle,
				struct ocfs2_caching_info *ci,
				struct buffer_head *ref_root_bh,
				struct buffer_head *ref_leaf_bh,
				int index, u64 cpos, unsigned int len,
				struct ocfs2_alloc_context *meta_ac,
				struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_rec *rec = &rb->rf_records.rl_recs[index];

	BUG_ON(cpos < le64_to_cpu(rec->r_cpos));
	BUG_ON(cpos + len >
	       le64_to_cpu(rec->r_cpos) + le32_to_cpu(rec->r_clusters));

	trace_ocfs2_decrease_refcount_rec(
		(unsigned long long)ocfs2_metadata_cache_owner(ci),
		(unsigned long long)cpos, len);

	if (cpos == le64_to_cpu(rec->r_cpos) &&
	    len == le32_to_cpu(rec->r_clusters))
		ret = ocfs2_change_refcount_rec(handle, ci,
						ref_leaf_bh, index, 1, -1);
	else {
		struct ocfs2_refcount_rec split = *rec;
		split.r_cpos = cpu_to_le64(cpos);
		split.r_clusters = cpu_to_le32(len);

		le32_add_cpu(&split.r_refcount, -1);

		ret = ocfs2_split_refcount_rec(handle, ci,
					       ref_root_bh, ref_leaf_bh,
					       &split, index, 1,
					       meta_ac, dealloc);
	}

	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/* Remove the leaf refcount block if it contains no refcount record. */
	if (!rb->rf_records.rl_used && ref_leaf_bh != ref_root_bh) {
		ret = ocfs2_remove_refcount_extent(handle, ci, ref_root_bh,
						   ref_leaf_bh, meta_ac,
						   dealloc);
		if (ret)
			mlog_errno(ret);
	}

out:
	return ret;
}