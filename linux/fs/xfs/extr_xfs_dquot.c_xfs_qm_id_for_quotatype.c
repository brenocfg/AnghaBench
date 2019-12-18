#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int uint ;
struct TYPE_2__ {int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; } ;
struct xfs_inode {TYPE_1__ i_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 
 int /*<<< orphan*/  xfs_get_projid (struct xfs_inode*) ; 

xfs_dqid_t
xfs_qm_id_for_quotatype(
	struct xfs_inode	*ip,
	uint			type)
{
	switch (type) {
	case XFS_DQ_USER:
		return ip->i_d.di_uid;
	case XFS_DQ_GROUP:
		return ip->i_d.di_gid;
	case XFS_DQ_PROJ:
		return xfs_get_projid(ip);
	}
	ASSERT(0);
	return 0;
}