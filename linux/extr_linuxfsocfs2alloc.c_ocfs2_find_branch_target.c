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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_extent_tree {struct ocfs2_extent_list* et_root_el; int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_list {scalar_t__ l_tree_depth; scalar_t__ l_next_free_rec; scalar_t__ l_count; TYPE_1__* l_recs; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  e_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_find_branch_target(struct ocfs2_extent_tree *et,
				    struct buffer_head **target_bh)
{
	int status = 0, i;
	u64 blkno;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list  *el;
	struct buffer_head *bh = NULL;
	struct buffer_head *lowest_bh = NULL;

	*target_bh = NULL;

	el = et->et_root_el;

	while(le16_to_cpu(el->l_tree_depth) > 1) {
		if (le16_to_cpu(el->l_next_free_rec) == 0) {
			status = ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
					"Owner %llu has empty extent list (next_free_rec == 0)\n",
					(unsigned long long)ocfs2_metadata_cache_owner(et->et_ci));
			goto bail;
		}
		i = le16_to_cpu(el->l_next_free_rec) - 1;
		blkno = le64_to_cpu(el->l_recs[i].e_blkno);
		if (!blkno) {
			status = ocfs2_error(ocfs2_metadata_cache_get_super(et->et_ci),
					"Owner %llu has extent list where extent # %d has no physical block start\n",
					(unsigned long long)ocfs2_metadata_cache_owner(et->et_ci), i);
			goto bail;
		}

		brelse(bh);
		bh = NULL;

		status = ocfs2_read_extent_block(et->et_ci, blkno, &bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		eb = (struct ocfs2_extent_block *) bh->b_data;
		el = &eb->h_list;

		if (le16_to_cpu(el->l_next_free_rec) <
		    le16_to_cpu(el->l_count)) {
			brelse(lowest_bh);
			lowest_bh = bh;
			get_bh(lowest_bh);
		}
	}

	/* If we didn't find one and the fe doesn't have any room,
	 * then return '1' */
	el = et->et_root_el;
	if (!lowest_bh && (el->l_next_free_rec == el->l_count))
		status = 1;

	*target_bh = lowest_bh;
bail:
	brelse(bh);

	return status;
}