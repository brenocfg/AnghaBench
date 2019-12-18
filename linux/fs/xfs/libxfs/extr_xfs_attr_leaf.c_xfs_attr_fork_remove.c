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
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {scalar_t__ di_anextents; int /*<<< orphan*/  di_aformat; scalar_t__ di_forkoff; } ;
struct xfs_inode {int /*<<< orphan*/ * i_afp; TYPE_1__ i_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DINODE_FMT_EXTENTS ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  xfs_idestroy_fork (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 

void
xfs_attr_fork_remove(
	struct xfs_inode	*ip,
	struct xfs_trans	*tp)
{
	xfs_idestroy_fork(ip, XFS_ATTR_FORK);
	ip->i_d.di_forkoff = 0;
	ip->i_d.di_aformat = XFS_DINODE_FMT_EXTENTS;

	ASSERT(ip->i_d.di_anextents == 0);
	ASSERT(ip->i_afp == NULL);

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
}