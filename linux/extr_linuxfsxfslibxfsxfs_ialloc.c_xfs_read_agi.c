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
 int /*<<< orphan*/  XFS_AGI_DADDR (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_AGI_REF ; 
 int /*<<< orphan*/  XFS_AG_DADDR (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BLFT_AGI_BUF ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  trace_xfs_read_agi (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_agi_buf_ops ; 
 int /*<<< orphan*/  xfs_buf_set_ref (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_trans_read_buf (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ *) ; 

int
xfs_read_agi(
	struct xfs_mount	*mp,	/* file system mount structure */
	struct xfs_trans	*tp,	/* transaction pointer */
	xfs_agnumber_t		agno,	/* allocation group number */
	struct xfs_buf		**bpp)	/* allocation group hdr buf */
{
	int			error;

	trace_xfs_read_agi(mp, agno);

	ASSERT(agno != NULLAGNUMBER);
	error = xfs_trans_read_buf(mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_AGI_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, bpp, &xfs_agi_buf_ops);
	if (error)
		return error;
	if (tp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_AGI_BUF);

	xfs_buf_set_ref(*bpp, XFS_AGI_REF);
	return 0;
}