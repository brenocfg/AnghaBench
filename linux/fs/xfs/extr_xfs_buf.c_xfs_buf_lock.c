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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_sema; int /*<<< orphan*/  b_mount; int /*<<< orphan*/  b_pin_count; } ;

/* Variables and functions */
 int XBF_STALE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_lock (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_lock_done (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_buf_lock(
	struct xfs_buf		*bp)
{
	trace_xfs_buf_lock(bp, _RET_IP_);

	if (atomic_read(&bp->b_pin_count) && (bp->b_flags & XBF_STALE))
		xfs_log_force(bp->b_mount, 0);
	down(&bp->b_sema);

	trace_xfs_buf_lock_done(bp, _RET_IP_);
}