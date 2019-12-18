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
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 scalar_t__ NULLAGNUMBER ; 
 int /*<<< orphan*/  XFS_AG_DADDR (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_SB_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_buf_oneshot (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_sb_buf_ops ; 
 struct xfs_buf* xfs_trans_get_buf (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_sb_get_secondary(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	struct xfs_buf		**bpp)
{
	struct xfs_buf		*bp;

	ASSERT(agno != 0 && agno != NULLAGNUMBER);
	bp = xfs_trans_get_buf(tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_SB_BLOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0);
	if (!bp)
		return -ENOMEM;
	bp->b_ops = &xfs_sb_buf_ops;
	xfs_buf_oneshot(bp);
	*bpp = bp;
	return 0;
}