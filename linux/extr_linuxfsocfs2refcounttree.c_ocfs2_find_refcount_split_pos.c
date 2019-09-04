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
struct ocfs2_refcount_list {int /*<<< orphan*/ * rl_recs; int /*<<< orphan*/  rl_used; } ;

/* Variables and functions */
 int ENOSPC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_get_ref_rec_low_cpos (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_refcount_rec_no_intersect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_find_refcount_split_pos(struct ocfs2_refcount_list *rl,
					 u32 *split_pos, int *split_index)
{
	int num_used = le16_to_cpu(rl->rl_used);
	int delta, middle = num_used / 2;

	for (delta = 0; delta < middle; delta++) {
		/* Let's check delta earlier than middle */
		if (ocfs2_refcount_rec_no_intersect(
					&rl->rl_recs[middle - delta - 1],
					&rl->rl_recs[middle - delta])) {
			*split_index = middle - delta;
			break;
		}

		/* For even counts, don't walk off the end */
		if ((middle + delta + 1) == num_used)
			continue;

		/* Now try delta past middle */
		if (ocfs2_refcount_rec_no_intersect(
					&rl->rl_recs[middle + delta],
					&rl->rl_recs[middle + delta + 1])) {
			*split_index = middle + delta + 1;
			break;
		}
	}

	if (delta >= middle)
		return -ENOSPC;

	*split_pos = ocfs2_get_ref_rec_low_cpos(&rl->rl_recs[*split_index]);
	return 0;
}