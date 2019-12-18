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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_iowait; int /*<<< orphan*/  (* b_iodone ) (struct xfs_buf*) ;int /*<<< orphan*/  b_error; TYPE_1__* b_ops; scalar_t__ b_io_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* verify_read ) (struct xfs_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_ASYNC ; 
 int XBF_DONE ; 
 int XBF_READ ; 
 int XBF_READ_AHEAD ; 
 int XBF_WRITE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xfs_buf*) ; 
 int /*<<< orphan*/  stub2 (struct xfs_buf*) ; 
 int /*<<< orphan*/  trace_xfs_buf_iodone (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_ioerror (struct xfs_buf*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 

void
xfs_buf_ioend(
	struct xfs_buf	*bp)
{
	bool		read = bp->b_flags & XBF_READ;

	trace_xfs_buf_iodone(bp, _RET_IP_);

	bp->b_flags &= ~(XBF_READ | XBF_WRITE | XBF_READ_AHEAD);

	/*
	 * Pull in IO completion errors now. We are guaranteed to be running
	 * single threaded, so we don't need the lock to read b_io_error.
	 */
	if (!bp->b_error && bp->b_io_error)
		xfs_buf_ioerror(bp, bp->b_io_error);

	/* Only validate buffers that were read without errors */
	if (read && !bp->b_error && bp->b_ops) {
		ASSERT(!bp->b_iodone);
		bp->b_ops->verify_read(bp);
	}

	if (!bp->b_error)
		bp->b_flags |= XBF_DONE;

	if (bp->b_iodone)
		(*(bp->b_iodone))(bp);
	else if (bp->b_flags & XBF_ASYNC)
		xfs_buf_relse(bp);
	else
		complete(&bp->b_iowait);
}