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
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int XFS_DQ_ALLTYPES ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 
 int XFS_IS_GQUOTA_ON (struct xfs_mount*) ; 
 int XFS_IS_PQUOTA_ON (struct xfs_mount*) ; 
 int XFS_IS_UQUOTA_ON (struct xfs_mount*) ; 

__attribute__((used)) static inline int xfs_this_quota_on(struct xfs_mount *mp, int type)
{
	switch (type & XFS_DQ_ALLTYPES) {
	case XFS_DQ_USER:
		return XFS_IS_UQUOTA_ON(mp);
	case XFS_DQ_GROUP:
		return XFS_IS_GQUOTA_ON(mp);
	case XFS_DQ_PROJ:
		return XFS_IS_PQUOTA_ON(mp);
	default:
		return 0;
	}
}