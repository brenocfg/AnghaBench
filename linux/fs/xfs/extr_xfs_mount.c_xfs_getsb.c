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
struct xfs_mount {struct xfs_buf* m_sb_bp; } ;
struct xfs_buf {int b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_DONE ; 
 int /*<<< orphan*/  xfs_buf_hold (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_lock (struct xfs_buf*) ; 

struct xfs_buf *
xfs_getsb(
	struct xfs_mount	*mp)
{
	struct xfs_buf		*bp = mp->m_sb_bp;

	xfs_buf_lock(bp);
	xfs_buf_hold(bp);
	ASSERT(bp->b_flags & XBF_DONE);
	return bp;
}