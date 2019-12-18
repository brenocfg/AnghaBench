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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_perag {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_AG_RESV_METADATA ; 
 int /*<<< orphan*/  XFS_AG_RESV_RMAPBT ; 
 scalar_t__ xfs_ag_resv_critical (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int /*<<< orphan*/  xfs_sb_version_hasrmapbt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xfs_reflink_ag_has_free_space(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno)
{
	struct xfs_perag	*pag;
	int			error = 0;

	if (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		return 0;

	pag = xfs_perag_get(mp, agno);
	if (xfs_ag_resv_critical(pag, XFS_AG_RESV_RMAPBT) ||
	    xfs_ag_resv_critical(pag, XFS_AG_RESV_METADATA))
		error = -ENOSPC;
	xfs_perag_put(pag);
	return error;
}