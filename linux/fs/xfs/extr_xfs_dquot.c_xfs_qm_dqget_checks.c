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
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 
 int /*<<< orphan*/  XFS_IS_GQUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_PQUOTA_ON (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_IS_UQUOTA_ON (struct xfs_mount*) ; 

__attribute__((used)) static int
xfs_qm_dqget_checks(
	struct xfs_mount	*mp,
	uint			type)
{
	if (WARN_ON_ONCE(!XFS_IS_QUOTA_RUNNING(mp)))
		return -ESRCH;

	switch (type) {
	case XFS_DQ_USER:
		if (!XFS_IS_UQUOTA_ON(mp))
			return -ESRCH;
		return 0;
	case XFS_DQ_GROUP:
		if (!XFS_IS_GQUOTA_ON(mp))
			return -ESRCH;
		return 0;
	case XFS_DQ_PROJ:
		if (!XFS_IS_PQUOTA_ON(mp))
			return -ESRCH;
		return 0;
	default:
		WARN_ON_ONCE(0);
		return -EINVAL;
	}
}