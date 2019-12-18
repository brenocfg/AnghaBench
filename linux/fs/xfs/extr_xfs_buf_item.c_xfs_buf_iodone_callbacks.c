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
struct xfs_buf {int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_li_list; int /*<<< orphan*/ * b_log_item; scalar_t__ b_first_retry_time; scalar_t__ b_retries; scalar_t__ b_last_error; scalar_t__ b_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_do_callbacks (struct xfs_buf*) ; 
 scalar_t__ xfs_buf_iodone_callback_error (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_ioend (struct xfs_buf*) ; 

void
xfs_buf_iodone_callbacks(
	struct xfs_buf		*bp)
{
	/*
	 * If there is an error, process it. Some errors require us
	 * to run callbacks after failure processing is done so we
	 * detect that and take appropriate action.
	 */
	if (bp->b_error && xfs_buf_iodone_callback_error(bp))
		return;

	/*
	 * Successful IO or permanent error. Either way, we can clear the
	 * retry state here in preparation for the next error that may occur.
	 */
	bp->b_last_error = 0;
	bp->b_retries = 0;
	bp->b_first_retry_time = 0;

	xfs_buf_do_callbacks(bp);
	bp->b_log_item = NULL;
	list_del_init(&bp->b_li_list);
	bp->b_iodone = NULL;
	xfs_buf_ioend(bp);
}