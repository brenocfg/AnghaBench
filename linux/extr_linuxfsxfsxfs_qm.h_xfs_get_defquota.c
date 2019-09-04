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
struct xfs_def_quota {int dummy; } ;
struct xfs_quotainfo {struct xfs_def_quota qi_prj_default; struct xfs_def_quota qi_grp_default; struct xfs_def_quota qi_usr_default; } ;
struct xfs_dquot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_QM_ISGDQ (struct xfs_dquot*) ; 
 int /*<<< orphan*/  XFS_QM_ISPDQ (struct xfs_dquot*) ; 
 scalar_t__ XFS_QM_ISUDQ (struct xfs_dquot*) ; 

__attribute__((used)) static inline struct xfs_def_quota *
xfs_get_defquota(struct xfs_dquot *dqp, struct xfs_quotainfo *qi)
{
	struct xfs_def_quota *defq;

	if (XFS_QM_ISUDQ(dqp))
		defq = &qi->qi_usr_default;
	else if (XFS_QM_ISGDQ(dqp))
		defq = &qi->qi_grp_default;
	else {
		ASSERT(XFS_QM_ISPDQ(dqp));
		defq = &qi->qi_prj_default;
	}
	return defq;
}