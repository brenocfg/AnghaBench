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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_META_IO_ERROR ; 
 int XBF_ASYNC ; 
 int XBF_DONE ; 
 int XBF_READ ; 
 int XBF_WRITE ; 
 int XBF_WRITE_FAIL ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  xfs_buf_islocked (struct xfs_buf*) ; 
 int xfs_buf_submit (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_force_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_bwrite(
	struct xfs_buf		*bp)
{
	int			error;

	ASSERT(xfs_buf_islocked(bp));

	bp->b_flags |= XBF_WRITE;
	bp->b_flags &= ~(XBF_ASYNC | XBF_READ | _XBF_DELWRI_Q |
			 XBF_WRITE_FAIL | XBF_DONE);

	error = xfs_buf_submit(bp);
	if (error)
		xfs_force_shutdown(bp->b_mount, SHUTDOWN_META_IO_ERROR);
	return error;
}