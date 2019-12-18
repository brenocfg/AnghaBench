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
struct ocfs2_dio_write_ctxt {int /*<<< orphan*/  dw_writer_pid; scalar_t__ dw_orphaned; scalar_t__ dw_zero_count; int /*<<< orphan*/  dw_zero_list; } ;
struct buffer_head {struct ocfs2_dio_write_ctxt* b_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct ocfs2_dio_write_ctxt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocfs2_dio_write_ctxt *
ocfs2_dio_alloc_write_ctx(struct buffer_head *bh, int *alloc)
{
	struct ocfs2_dio_write_ctxt *dwc = NULL;

	if (bh->b_private)
		return bh->b_private;

	dwc = kmalloc(sizeof(struct ocfs2_dio_write_ctxt), GFP_NOFS);
	if (dwc == NULL)
		return NULL;
	INIT_LIST_HEAD(&dwc->dw_zero_list);
	dwc->dw_zero_count = 0;
	dwc->dw_orphaned = 0;
	dwc->dw_writer_pid = task_pid_nr(current);
	bh->b_private = dwc;
	*alloc = 1;

	return dwc;
}