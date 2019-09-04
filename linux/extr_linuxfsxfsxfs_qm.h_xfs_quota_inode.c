#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* m_quotainfo; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int uint ;
struct xfs_inode {int dummy; } ;
struct TYPE_4__ {struct xfs_inode* qi_pquotaip; struct xfs_inode* qi_gquotaip; struct xfs_inode* qi_uquotaip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int XFS_DQ_ALLTYPES ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 

__attribute__((used)) static inline struct xfs_inode *
xfs_quota_inode(xfs_mount_t *mp, uint dq_flags)
{
	switch (dq_flags & XFS_DQ_ALLTYPES) {
	case XFS_DQ_USER:
		return mp->m_quotainfo->qi_uquotaip;
	case XFS_DQ_GROUP:
		return mp->m_quotainfo->qi_gquotaip;
	case XFS_DQ_PROJ:
		return mp->m_quotainfo->qi_pquotaip;
	default:
		ASSERT(0);
	}
	return NULL;
}