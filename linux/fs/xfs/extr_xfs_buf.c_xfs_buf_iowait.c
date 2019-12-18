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
struct xfs_buf {int b_flags; int b_error; int /*<<< orphan*/  b_iowait; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_ASYNC ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_buf_iowait (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_iowait_done (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xfs_buf_iowait(
	struct xfs_buf	*bp)
{
	ASSERT(!(bp->b_flags & XBF_ASYNC));

	trace_xfs_buf_iowait(bp, _RET_IP_);
	wait_for_completion(&bp->b_iowait);
	trace_xfs_buf_iowait_done(bp, _RET_IP_);

	return bp->b_error;
}