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
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {scalar_t__ l_next_free_rec; scalar_t__ l_tree_depth; scalar_t__ l_count; int /*<<< orphan*/ * l_recs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int,int) ; 
 scalar_t__ ocfs2_is_empty_extent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_shift_records_right (struct ocfs2_extent_list*) ; 

__attribute__((used)) static void ocfs2_create_empty_extent(struct ocfs2_extent_list *el)
{
	int next_free = le16_to_cpu(el->l_next_free_rec);

	BUG_ON(le16_to_cpu(el->l_tree_depth) != 0);

	if (next_free == 0)
		goto set_and_inc;

	if (ocfs2_is_empty_extent(&el->l_recs[0]))
		return;

	mlog_bug_on_msg(el->l_count == el->l_next_free_rec,
			"Asked to create an empty extent in a full list:\n"
			"count = %u, tree depth = %u",
			le16_to_cpu(el->l_count),
			le16_to_cpu(el->l_tree_depth));

	ocfs2_shift_records_right(el);

set_and_inc:
	le16_add_cpu(&el->l_next_free_rec, 1);
	memset(&el->l_recs[0], 0, sizeof(struct ocfs2_extent_rec));
}