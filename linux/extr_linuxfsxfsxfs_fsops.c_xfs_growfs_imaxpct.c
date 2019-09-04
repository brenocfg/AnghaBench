#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int dummy; } ;
struct TYPE_3__ {int sb_imax_pct; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tr_growdata; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_GROWFS_SPACE_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_TRANS_RESERVE ; 
 int /*<<< orphan*/  XFS_TRANS_SB_IMAXPCT ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_mod_sb (struct xfs_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

__attribute__((used)) static int
xfs_growfs_imaxpct(
	struct xfs_mount	*mp,
	__u32			imaxpct)
{
	struct xfs_trans	*tp;
	int			dpct;
	int			error;

	if (imaxpct > 100)
		return -EINVAL;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growdata,
			XFS_GROWFS_SPACE_RES(mp), 0, XFS_TRANS_RESERVE, &tp);
	if (error)
		return error;

	dpct = imaxpct - mp->m_sb.sb_imax_pct;
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_IMAXPCT, dpct);
	xfs_trans_set_sync(tp);
	return xfs_trans_commit(tp);
}