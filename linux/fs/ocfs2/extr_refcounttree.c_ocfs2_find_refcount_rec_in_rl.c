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
struct ocfs2_refcount_rec {void* r_clusters; int /*<<< orphan*/  r_cpos; scalar_t__ r_refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  rl_used; struct ocfs2_refcount_rec* rl_recs; } ;
struct ocfs2_refcount_block {TYPE_1__ rf_records; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_find_refcount_rec_in_rl(struct ocfs2_caching_info *ci,
					  struct buffer_head *ref_leaf_bh,
					  u64 cpos, unsigned int len,
					  struct ocfs2_refcount_rec *ret_rec,
					  int *index)
{
	int i = 0;
	struct ocfs2_refcount_block *rb =
		(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_rec *rec = NULL;

	for (; i < le16_to_cpu(rb->rf_records.rl_used); i++) {
		rec = &rb->rf_records.rl_recs[i];

		if (le64_to_cpu(rec->r_cpos) +
		    le32_to_cpu(rec->r_clusters) <= cpos)
			continue;
		else if (le64_to_cpu(rec->r_cpos) > cpos)
			break;

		/* ok, cpos fail in this rec. Just return. */
		if (ret_rec)
			*ret_rec = *rec;
		goto out;
	}

	if (ret_rec) {
		/* We meet with a hole here, so fake the rec. */
		ret_rec->r_cpos = cpu_to_le64(cpos);
		ret_rec->r_refcount = 0;
		if (i < le16_to_cpu(rb->rf_records.rl_used) &&
		    le64_to_cpu(rec->r_cpos) < cpos + len)
			ret_rec->r_clusters =
				cpu_to_le32(le64_to_cpu(rec->r_cpos) - cpos);
		else
			ret_rec->r_clusters = cpu_to_le32(len);
	}

out:
	*index = i;
}