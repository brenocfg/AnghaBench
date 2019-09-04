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
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NULLAGNUMBER ; 
 int /*<<< orphan*/  XFS_AG_DADDR (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_SB_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_SSB_REF ; 
 int /*<<< orphan*/  xfs_buf_set_ref (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_buf_ops ; 
 int xfs_trans_read_buf (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ *) ; 

int
xfs_sb_read_secondary(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	struct xfs_buf		**bpp)
{
	struct xfs_buf		*bp;
	int			error;

	ASSERT(agno != 0 && agno != NULLAGNUMBER);
	error = xfs_trans_read_buf(mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_SB_BLOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp, &xfs_sb_buf_ops);
	if (error)
		return error;
	xfs_buf_set_ref(bp, XFS_SSB_REF);
	*bpp = bp;
	return 0;
}