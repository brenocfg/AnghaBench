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
struct ocfs2_super {int /*<<< orphan*/  local_alloc_bits; } ;
struct ocfs2_alloc_context {struct buffer_head* ac_bh; struct inode* ac_inode; int /*<<< orphan*/  ac_bits_wanted; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OCFS2_LA_DISABLED ; 
 int /*<<< orphan*/  OCFS2_LA_EVENT_ENOSPC ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 struct ocfs2_alloc_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_alloc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 scalar_t__ ocfs2_recalc_la_window (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_reserve_cluster_bitmap_bits (struct ocfs2_super*,struct ocfs2_alloc_context*) ; 

__attribute__((used)) static int ocfs2_local_alloc_reserve_for_window(struct ocfs2_super *osb,
						struct ocfs2_alloc_context **ac,
						struct inode **bitmap_inode,
						struct buffer_head **bitmap_bh)
{
	int status;

	*ac = kzalloc(sizeof(struct ocfs2_alloc_context), GFP_KERNEL);
	if (!(*ac)) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

retry_enospc:
	(*ac)->ac_bits_wanted = osb->local_alloc_bits;
	status = ocfs2_reserve_cluster_bitmap_bits(osb, *ac);
	if (status == -ENOSPC) {
		if (ocfs2_recalc_la_window(osb, OCFS2_LA_EVENT_ENOSPC) ==
		    OCFS2_LA_DISABLED)
			goto bail;

		ocfs2_free_ac_resource(*ac);
		memset(*ac, 0, sizeof(struct ocfs2_alloc_context));
		goto retry_enospc;
	}
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	*bitmap_inode = (*ac)->ac_inode;
	igrab(*bitmap_inode);
	*bitmap_bh = (*ac)->ac_bh;
	get_bh(*bitmap_bh);
	status = 0;
bail:
	if ((status < 0) && *ac) {
		ocfs2_free_alloc_context(*ac);
		*ac = NULL;
	}

	if (status)
		mlog_errno(status);
	return status;
}