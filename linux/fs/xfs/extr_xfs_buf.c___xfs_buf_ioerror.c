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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
struct TYPE_4__ {int b_error; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  trace_xfs_buf_ioerror (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
__xfs_buf_ioerror(
	xfs_buf_t		*bp,
	int			error,
	xfs_failaddr_t		failaddr)
{
	ASSERT(error <= 0 && error >= -1000);
	bp->b_error = error;
	trace_xfs_buf_ioerror(bp, error, failaddr);
}