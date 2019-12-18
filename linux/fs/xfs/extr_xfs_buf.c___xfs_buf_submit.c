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
struct xfs_buf {int b_flags; scalar_t__ b_error; int /*<<< orphan*/  b_io_remaining; scalar_t__ b_io_error; int /*<<< orphan*/  b_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int XBF_ASYNC ; 
 int XBF_DONE ; 
 int XBF_WRITE ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  _xfs_buf_ioapply (struct xfs_buf*) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_xfs_buf_submit (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_hold (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_ioacct_inc (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_ioend (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_ioend_async (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_ioerror (struct xfs_buf*,int) ; 
 int xfs_buf_iowait (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_rele (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_stale (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_wait_unpin (struct xfs_buf*) ; 

int
__xfs_buf_submit(
	struct xfs_buf	*bp,
	bool		wait)
{
	int		error = 0;

	trace_xfs_buf_submit(bp, _RET_IP_);

	ASSERT(!(bp->b_flags & _XBF_DELWRI_Q));

	/* on shutdown we stale and complete the buffer immediately */
	if (XFS_FORCED_SHUTDOWN(bp->b_mount)) {
		xfs_buf_ioerror(bp, -EIO);
		bp->b_flags &= ~XBF_DONE;
		xfs_buf_stale(bp);
		xfs_buf_ioend(bp);
		return -EIO;
	}

	/*
	 * Grab a reference so the buffer does not go away underneath us. For
	 * async buffers, I/O completion drops the callers reference, which
	 * could occur before submission returns.
	 */
	xfs_buf_hold(bp);

	if (bp->b_flags & XBF_WRITE)
		xfs_buf_wait_unpin(bp);

	/* clear the internal error state to avoid spurious errors */
	bp->b_io_error = 0;

	/*
	 * Set the count to 1 initially, this will stop an I/O completion
	 * callout which happens before we have started all the I/O from calling
	 * xfs_buf_ioend too early.
	 */
	atomic_set(&bp->b_io_remaining, 1);
	if (bp->b_flags & XBF_ASYNC)
		xfs_buf_ioacct_inc(bp);
	_xfs_buf_ioapply(bp);

	/*
	 * If _xfs_buf_ioapply failed, we can get back here with only the IO
	 * reference we took above. If we drop it to zero, run completion so
	 * that we don't return to the caller with completion still pending.
	 */
	if (atomic_dec_and_test(&bp->b_io_remaining) == 1) {
		if (bp->b_error || !(bp->b_flags & XBF_ASYNC))
			xfs_buf_ioend(bp);
		else
			xfs_buf_ioend_async(bp);
	}

	if (wait)
		error = xfs_buf_iowait(bp);

	/*
	 * Release the hold that keeps the buffer referenced for the entire
	 * I/O. Note that if the buffer is async, it is not safe to reference
	 * after this release.
	 */
	xfs_buf_rele(bp);
	return error;
}