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
struct xfs_buf {int /*<<< orphan*/  b_sema; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_buf_unlock (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_islocked (struct xfs_buf*) ; 

void
xfs_buf_unlock(
	struct xfs_buf		*bp)
{
	ASSERT(xfs_buf_islocked(bp));

	up(&bp->b_sema);
	trace_xfs_buf_unlock(bp, _RET_IP_);
}