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
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_trylock (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_trylock_fail (struct xfs_buf*,int /*<<< orphan*/ ) ; 

int
xfs_buf_trylock(
	struct xfs_buf		*bp)
{
	int			locked;

	locked = down_trylock(&bp->b_sema) == 0;
	if (locked)
		trace_xfs_buf_trylock(bp, _RET_IP_);
	else
		trace_xfs_buf_trylock_fail(bp, _RET_IP_);
	return locked;
}