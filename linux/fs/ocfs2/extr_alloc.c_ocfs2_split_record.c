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
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; } ;
typedef  enum ocfs2_split_type { ____Placeholder_ocfs2_split_type } ocfs2_split_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SPLIT_LEFT ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_rotate_leaf (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int ocfs2_search_extent_list (struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_subtract_from_rec (int /*<<< orphan*/ ,int,struct ocfs2_extent_rec*,struct ocfs2_extent_rec*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static void ocfs2_split_record(struct ocfs2_extent_tree *et,
			       struct ocfs2_path *left_path,
			       struct ocfs2_path *right_path,
			       struct ocfs2_extent_rec *split_rec,
			       enum ocfs2_split_type split)
{
	int index;
	u32 cpos = le32_to_cpu(split_rec->e_cpos);
	struct ocfs2_extent_list *left_el = NULL, *right_el, *insert_el, *el;
	struct ocfs2_extent_rec *rec, *tmprec;

	right_el = path_leaf_el(right_path);
	if (left_path)
		left_el = path_leaf_el(left_path);

	el = right_el;
	insert_el = right_el;
	index = ocfs2_search_extent_list(el, cpos);
	if (index != -1) {
		if (index == 0 && left_path) {
			BUG_ON(ocfs2_is_empty_extent(&el->l_recs[0]));

			/*
			 * This typically means that the record
			 * started in the left path but moved to the
			 * right as a result of rotation. We either
			 * move the existing record to the left, or we
			 * do the later insert there.
			 *
			 * In this case, the left path should always
			 * exist as the rotate code will have passed
			 * it back for a post-insert update.
			 */

			if (split == SPLIT_LEFT) {
				/*
				 * It's a left split. Since we know
				 * that the rotate code gave us an
				 * empty extent in the left path, we
				 * can just do the insert there.
				 */
				insert_el = left_el;
			} else {
				/*
				 * Right split - we have to move the
				 * existing record over to the left
				 * leaf. The insert will be into the
				 * newly created empty extent in the
				 * right leaf.
				 */
				tmprec = &right_el->l_recs[index];
				ocfs2_rotate_leaf(left_el, tmprec);
				el = left_el;

				memset(tmprec, 0, sizeof(*tmprec));
				index = ocfs2_search_extent_list(left_el, cpos);
				BUG_ON(index == -1);
			}
		}
	} else {
		BUG_ON(!left_path);
		BUG_ON(!ocfs2_is_empty_extent(&left_el->l_recs[0]));
		/*
		 * Left path is easy - we can just allow the insert to
		 * happen.
		 */
		el = left_el;
		insert_el = left_el;
		index = ocfs2_search_extent_list(el, cpos);
		BUG_ON(index == -1);
	}

	rec = &el->l_recs[index];
	ocfs2_subtract_from_rec(ocfs2_metadata_cache_get_super(et->et_ci),
				split, rec, split_rec);
	ocfs2_rotate_leaf(insert_el, split_rec);
}