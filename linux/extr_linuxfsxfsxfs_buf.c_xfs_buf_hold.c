#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  b_hold; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_hold (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
xfs_buf_hold(
	xfs_buf_t		*bp)
{
	trace_xfs_buf_hold(bp, _RET_IP_);
	atomic_inc(&bp->b_hold);
}