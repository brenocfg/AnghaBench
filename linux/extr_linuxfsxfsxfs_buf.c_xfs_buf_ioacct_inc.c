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
struct xfs_buf {int b_flags; int b_state; int /*<<< orphan*/  b_lock; TYPE_1__* b_target; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_io_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_ASYNC ; 
 int XBF_NO_IOACCT ; 
 int XFS_BSTATE_IN_FLIGHT ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
xfs_buf_ioacct_inc(
	struct xfs_buf	*bp)
{
	if (bp->b_flags & XBF_NO_IOACCT)
		return;

	ASSERT(bp->b_flags & XBF_ASYNC);
	spin_lock(&bp->b_lock);
	if (!(bp->b_state & XFS_BSTATE_IN_FLIGHT)) {
		bp->b_state |= XFS_BSTATE_IN_FLIGHT;
		percpu_counter_inc(&bp->b_target->bt_io_count);
	}
	spin_unlock(&bp->b_lock);
}