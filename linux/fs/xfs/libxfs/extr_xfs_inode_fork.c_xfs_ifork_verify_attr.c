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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_2__ {scalar_t__ di_aformat; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct xfs_ifork_ops {int /*<<< orphan*/ * (* verify_attr ) (struct xfs_inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/  XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __this_address ; 
 int /*<<< orphan*/ * stub1 (struct xfs_inode*) ; 

xfs_failaddr_t
xfs_ifork_verify_attr(
	struct xfs_inode	*ip,
	struct xfs_ifork_ops	*ops)
{
	/* There has to be an attr fork allocated if aformat is local. */
	if (ip->i_d.di_aformat != XFS_DINODE_FMT_LOCAL)
		return NULL;
	if (!XFS_IFORK_PTR(ip, XFS_ATTR_FORK))
		return __this_address;
	return ops->verify_attr(ip);
}