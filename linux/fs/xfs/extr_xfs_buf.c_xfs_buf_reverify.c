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
struct xfs_buf_ops {int /*<<< orphan*/  (* verify_read ) (struct xfs_buf*) ;} ;
struct xfs_buf {int b_flags; scalar_t__ b_error; struct xfs_buf_ops const* b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_DONE ; 
 int /*<<< orphan*/  stub1 (struct xfs_buf*) ; 

int
xfs_buf_reverify(
	struct xfs_buf		*bp,
	const struct xfs_buf_ops *ops)
{
	ASSERT(bp->b_flags & XBF_DONE);
	ASSERT(bp->b_error == 0);

	if (!ops || bp->b_ops)
		return 0;

	bp->b_ops = ops;
	bp->b_ops->verify_read(bp);
	if (bp->b_error)
		bp->b_flags &= ~XBF_DONE;
	return bp->b_error;
}