#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_extent_list {TYPE_1__* l_recs; int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_tree_depth; } ;
struct TYPE_3__ {int /*<<< orphan*/  e_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_adjust_adjacent_records (TYPE_1__*,TYPE_1__*,struct ocfs2_extent_list*) ; 

__attribute__((used)) static void ocfs2_adjust_root_records(struct ocfs2_extent_list *root_el,
				      struct ocfs2_extent_list *left_el,
				      struct ocfs2_extent_list *right_el,
				      u64 left_el_blkno)
{
	int i;

	BUG_ON(le16_to_cpu(root_el->l_tree_depth) <=
	       le16_to_cpu(left_el->l_tree_depth));

	for(i = 0; i < le16_to_cpu(root_el->l_next_free_rec) - 1; i++) {
		if (le64_to_cpu(root_el->l_recs[i].e_blkno) == left_el_blkno)
			break;
	}

	/*
	 * The path walking code should have never returned a root and
	 * two paths which are not adjacent.
	 */
	BUG_ON(i >= (le16_to_cpu(root_el->l_next_free_rec) - 1));

	ocfs2_adjust_adjacent_records(&root_el->l_recs[i],
				      &root_el->l_recs[i + 1], right_el);
}