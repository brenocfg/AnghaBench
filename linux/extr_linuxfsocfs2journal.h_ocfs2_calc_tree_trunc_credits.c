#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct super_block {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/ * l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct TYPE_3__ {int /*<<< orphan*/  l_tree_depth; } ;
struct TYPE_4__ {TYPE_1__ i_list; } ;
struct ocfs2_dinode {TYPE_2__ id2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_TRUNCATE_LOG_UPDATE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_quota_trans_credits (struct super_block*) ; 
 unsigned int ocfs2_rec_clusters (struct ocfs2_extent_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ocfs2_calc_tree_trunc_credits(struct super_block *sb,
						unsigned int clusters_to_del,
						struct ocfs2_dinode *fe,
						struct ocfs2_extent_list *last_el)
{
 	/* for dinode + all headers in this pass + update to next leaf */
	u16 next_free = le16_to_cpu(last_el->l_next_free_rec);
	u16 tree_depth = le16_to_cpu(fe->id2.i_list.l_tree_depth);
	int credits = 1 + tree_depth + 1;
	int i;

	i = next_free - 1;
	BUG_ON(i < 0);

	/* We may be deleting metadata blocks, so metadata alloc dinode +
	   one desc. block for each possible delete. */
	if (tree_depth && next_free == 1 &&
	    ocfs2_rec_clusters(last_el, &last_el->l_recs[i]) == clusters_to_del)
		credits += 1 + tree_depth;

	/* update to the truncate log. */
	credits += OCFS2_TRUNCATE_LOG_UPDATE;

	credits += ocfs2_quota_trans_credits(sb);

	return credits;
}