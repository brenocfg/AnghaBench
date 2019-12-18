#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_7__ {int /*<<< orphan*/  m_ddev_targp; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
typedef  scalar_t__ xfs_agnumber_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NULLAGNUMBER ; 
 int /*<<< orphan*/  XFS_AGFL_DADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  XFS_AGFL_REF ; 
 int /*<<< orphan*/  XFS_AG_DADDR (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSS_TO_BB (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xfs_agfl_buf_ops ; 
 int /*<<< orphan*/  xfs_buf_set_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_read_buf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int					/* error */
xfs_alloc_read_agfl(
	xfs_mount_t	*mp,		/* mount point structure */
	xfs_trans_t	*tp,		/* transaction pointer */
	xfs_agnumber_t	agno,		/* allocation group number */
	xfs_buf_t	**bpp)		/* buffer for the ag free block array */
{
	xfs_buf_t	*bp;		/* return value */
	int		error;

	ASSERT(agno != NULLAGNUMBER);
	error = xfs_trans_read_buf(
			mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_AGFL_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp, &xfs_agfl_buf_ops);
	if (error)
		return error;
	xfs_buf_set_ref(bp, XFS_AGFL_REF);
	*bpp = bp;
	return 0;
}