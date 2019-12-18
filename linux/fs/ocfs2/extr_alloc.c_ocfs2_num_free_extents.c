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
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_list {scalar_t__ l_tree_depth; int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_count; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_et_get_last_eb_blk (struct ocfs2_extent_tree*) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  trace_ocfs2_num_free_extents (int) ; 

int ocfs2_num_free_extents(struct ocfs2_extent_tree *et)
{
	int retval;
	struct ocfs2_extent_list *el = NULL;
	struct ocfs2_extent_block *eb;
	struct buffer_head *eb_bh = NULL;
	u64 last_eb_blk = 0;

	el = et->et_root_el;
	last_eb_blk = ocfs2_et_get_last_eb_blk(et);

	if (last_eb_blk) {
		retval = ocfs2_read_extent_block(et->et_ci, last_eb_blk,
						 &eb_bh);
		if (retval < 0) {
			mlog_errno(retval);
			goto bail;
		}
		eb = (struct ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;
	}

	BUG_ON(el->l_tree_depth != 0);

	retval = le16_to_cpu(el->l_count) - le16_to_cpu(el->l_next_free_rec);
bail:
	brelse(eb_bh);

	trace_ocfs2_num_free_extents(retval);
	return retval;
}