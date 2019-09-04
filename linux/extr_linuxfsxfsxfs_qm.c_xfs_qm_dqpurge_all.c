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
typedef  int uint ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DQ_GROUP ; 
 int /*<<< orphan*/  XFS_DQ_PROJ ; 
 int /*<<< orphan*/  XFS_DQ_USER ; 
 int XFS_QMOPT_GQUOTA ; 
 int XFS_QMOPT_PQUOTA ; 
 int XFS_QMOPT_UQUOTA ; 
 int /*<<< orphan*/  xfs_qm_dqpurge ; 
 int /*<<< orphan*/  xfs_qm_dquot_walk (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_qm_dqpurge_all(
	struct xfs_mount	*mp,
	uint			flags)
{
	if (flags & XFS_QMOPT_UQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQ_USER, xfs_qm_dqpurge, NULL);
	if (flags & XFS_QMOPT_GQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQ_GROUP, xfs_qm_dqpurge, NULL);
	if (flags & XFS_QMOPT_PQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQ_PROJ, xfs_qm_dqpurge, NULL);
}