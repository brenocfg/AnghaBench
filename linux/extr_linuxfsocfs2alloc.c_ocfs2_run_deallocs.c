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
struct ocfs2_super {int dummy; } ;
struct ocfs2_per_slot_free_list {struct ocfs2_per_slot_free_list* f_next_suballocator; scalar_t__ f_first; int /*<<< orphan*/  f_slot; int /*<<< orphan*/  f_inode_type; } ;
struct ocfs2_cached_dealloc_ctxt {int /*<<< orphan*/ * c_global_allocator; struct ocfs2_per_slot_free_list* c_first_suballocator; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ocfs2_per_slot_free_list*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_free_cached_blocks (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_free_cached_clusters (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_run_deallocs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocfs2_run_deallocs(struct ocfs2_super *osb,
		       struct ocfs2_cached_dealloc_ctxt *ctxt)
{
	int ret = 0, ret2;
	struct ocfs2_per_slot_free_list *fl;

	if (!ctxt)
		return 0;

	while (ctxt->c_first_suballocator) {
		fl = ctxt->c_first_suballocator;

		if (fl->f_first) {
			trace_ocfs2_run_deallocs(fl->f_inode_type,
						 fl->f_slot);
			ret2 = ocfs2_free_cached_blocks(osb,
							fl->f_inode_type,
							fl->f_slot,
							fl->f_first);
			if (ret2)
				mlog_errno(ret2);
			if (!ret)
				ret = ret2;
		}

		ctxt->c_first_suballocator = fl->f_next_suballocator;
		kfree(fl);
	}

	if (ctxt->c_global_allocator) {
		ret2 = ocfs2_free_cached_clusters(osb,
						  ctxt->c_global_allocator);
		if (ret2)
			mlog_errno(ret2);
		if (!ret)
			ret = ret2;

		ctxt->c_global_allocator = NULL;
	}

	return ret;
}