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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_refcount_rec {int dummy; } ;
struct ocfs2_refcount_list {int /*<<< orphan*/  rl_used; int /*<<< orphan*/ * rl_recs; int /*<<< orphan*/  rl_count; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_cpos; struct ocfs2_refcount_list rf_records; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_refcount_rec_by_cpos ; 
 int /*<<< orphan*/  cmp_refcount_rec_by_low_cpos ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_find_refcount_split_pos (struct ocfs2_refcount_list*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_refcount_rec ; 
 int /*<<< orphan*/  trace_ocfs2_divide_leaf_refcount_block (unsigned long long,int,int) ; 

__attribute__((used)) static int ocfs2_divide_leaf_refcount_block(struct buffer_head *ref_leaf_bh,
					    struct buffer_head *new_bh,
					    u32 *split_cpos)
{
	int split_index = 0, num_moved, ret;
	u32 cpos = 0;
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_leaf_bh->b_data;
	struct ocfs2_refcount_list *rl = &rb->rf_records;
	struct ocfs2_refcount_block *new_rb =
			(struct ocfs2_refcount_block *)new_bh->b_data;
	struct ocfs2_refcount_list *new_rl = &new_rb->rf_records;

	trace_ocfs2_divide_leaf_refcount_block(
		(unsigned long long)ref_leaf_bh->b_blocknr,
		le16_to_cpu(rl->rl_count), le16_to_cpu(rl->rl_used));

	/*
	 * XXX: Improvement later.
	 * If we know all the high 32 bit cpos is the same, no need to sort.
	 *
	 * In order to make the whole process safe, we do:
	 * 1. sort the entries by their low 32 bit cpos first so that we can
	 *    find the split cpos easily.
	 * 2. call ocfs2_insert_extent to insert the new refcount block.
	 * 3. move the refcount rec to the new block.
	 * 4. sort the entries by their 64 bit cpos.
	 * 5. dirty the new_rb and rb.
	 */
	sort(&rl->rl_recs, le16_to_cpu(rl->rl_used),
	     sizeof(struct ocfs2_refcount_rec),
	     cmp_refcount_rec_by_low_cpos, swap_refcount_rec);

	ret = ocfs2_find_refcount_split_pos(rl, &cpos, &split_index);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	new_rb->rf_cpos = cpu_to_le32(cpos);

	/* move refcount records starting from split_index to the new block. */
	num_moved = le16_to_cpu(rl->rl_used) - split_index;
	memcpy(new_rl->rl_recs, &rl->rl_recs[split_index],
	       num_moved * sizeof(struct ocfs2_refcount_rec));

	/*ok, remove the entries we just moved over to the other block. */
	memset(&rl->rl_recs[split_index], 0,
	       num_moved * sizeof(struct ocfs2_refcount_rec));

	/* change old and new rl_used accordingly. */
	le16_add_cpu(&rl->rl_used, -num_moved);
	new_rl->rl_used = cpu_to_le16(num_moved);

	sort(&rl->rl_recs, le16_to_cpu(rl->rl_used),
	     sizeof(struct ocfs2_refcount_rec),
	     cmp_refcount_rec_by_cpos, swap_refcount_rec);

	sort(&new_rl->rl_recs, le16_to_cpu(new_rl->rl_used),
	     sizeof(struct ocfs2_refcount_rec),
	     cmp_refcount_rec_by_cpos, swap_refcount_rec);

	*split_cpos = cpos;
	return 0;
}