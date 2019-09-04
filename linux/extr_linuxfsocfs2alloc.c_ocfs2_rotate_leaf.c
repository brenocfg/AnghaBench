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
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_count; int /*<<< orphan*/  l_next_free_rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_extent_rec*,struct ocfs2_extent_rec*,int) ; 
 int ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  trace_ocfs2_rotate_leaf (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static void ocfs2_rotate_leaf(struct ocfs2_extent_list *el,
			      struct ocfs2_extent_rec *insert_rec)
{
	int i, insert_index, next_free, has_empty, num_bytes;
	u32 insert_cpos = le32_to_cpu(insert_rec->e_cpos);
	struct ocfs2_extent_rec *rec;

	next_free = le16_to_cpu(el->l_next_free_rec);
	has_empty = ocfs2_is_empty_extent(&el->l_recs[0]);

	BUG_ON(!next_free);

	/* The tree code before us didn't allow enough room in the leaf. */
	BUG_ON(el->l_next_free_rec == el->l_count && !has_empty);

	/*
	 * The easiest way to approach this is to just remove the
	 * empty extent and temporarily decrement next_free.
	 */
	if (has_empty) {
		/*
		 * If next_free was 1 (only an empty extent), this
		 * loop won't execute, which is fine. We still want
		 * the decrement above to happen.
		 */
		for(i = 0; i < (next_free - 1); i++)
			el->l_recs[i] = el->l_recs[i+1];

		next_free--;
	}

	/*
	 * Figure out what the new record index should be.
	 */
	for(i = 0; i < next_free; i++) {
		rec = &el->l_recs[i];

		if (insert_cpos < le32_to_cpu(rec->e_cpos))
			break;
	}
	insert_index = i;

	trace_ocfs2_rotate_leaf(insert_cpos, insert_index,
				has_empty, next_free,
				le16_to_cpu(el->l_count));

	BUG_ON(insert_index < 0);
	BUG_ON(insert_index >= le16_to_cpu(el->l_count));
	BUG_ON(insert_index > next_free);

	/*
	 * No need to memmove if we're just adding to the tail.
	 */
	if (insert_index != next_free) {
		BUG_ON(next_free >= le16_to_cpu(el->l_count));

		num_bytes = next_free - insert_index;
		num_bytes *= sizeof(struct ocfs2_extent_rec);
		memmove(&el->l_recs[insert_index + 1],
			&el->l_recs[insert_index],
			num_bytes);
	}

	/*
	 * Either we had an empty extent, and need to re-increment or
	 * there was no empty extent on a non full rightmost leaf node,
	 * in which case we still need to increment.
	 */
	next_free++;
	el->l_next_free_rec = cpu_to_le16(next_free);
	/*
	 * Make sure none of the math above just messed up our tree.
	 */
	BUG_ON(le16_to_cpu(el->l_next_free_rec) > le16_to_cpu(el->l_count));

	el->l_recs[insert_index] = *insert_rec;

}