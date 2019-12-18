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
struct ocfs2_extent_rec {scalar_t__ e_leaf_clusters; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_extent_rec*,struct ocfs2_extent_rec*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 

__attribute__((used)) static void ocfs2_cleanup_merge(struct ocfs2_extent_list *el,
				int index)
{
	struct ocfs2_extent_rec *rec = &el->l_recs[index];
	unsigned int size;

	if (rec->e_leaf_clusters == 0) {
		/*
		 * We consumed all of the merged-from record. An empty
		 * extent cannot exist anywhere but the 1st array
		 * position, so move things over if the merged-from
		 * record doesn't occupy that position.
		 *
		 * This creates a new empty extent so the caller
		 * should be smart enough to have removed any existing
		 * ones.
		 */
		if (index > 0) {
			BUG_ON(ocfs2_is_empty_extent(&el->l_recs[0]));
			size = index * sizeof(struct ocfs2_extent_rec);
			memmove(&el->l_recs[1], &el->l_recs[0], size);
		}

		/*
		 * Always memset - the caller doesn't check whether it
		 * created an empty extent, so there could be junk in
		 * the other fields.
		 */
		memset(&el->l_recs[0], 0, sizeof(struct ocfs2_extent_rec));
	}
}