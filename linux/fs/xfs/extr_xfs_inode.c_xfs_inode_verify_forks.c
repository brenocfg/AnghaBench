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
typedef  scalar_t__ xfs_failaddr_t ;
struct xfs_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * if_data; } ;
struct xfs_ifork {int /*<<< orphan*/  if_bytes; TYPE_1__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_default_ifork_ops ; 
 scalar_t__ xfs_ifork_verify_attr (struct xfs_inode*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_ifork_verify_data (struct xfs_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_inode_verifier_error (struct xfs_inode*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

bool
xfs_inode_verify_forks(
	struct xfs_inode	*ip)
{
	struct xfs_ifork	*ifp;
	xfs_failaddr_t		fa;

	fa = xfs_ifork_verify_data(ip, &xfs_default_ifork_ops);
	if (fa) {
		ifp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
		xfs_inode_verifier_error(ip, -EFSCORRUPTED, "data fork",
				ifp->if_u1.if_data, ifp->if_bytes, fa);
		return false;
	}

	fa = xfs_ifork_verify_attr(ip, &xfs_default_ifork_ops);
	if (fa) {
		ifp = XFS_IFORK_PTR(ip, XFS_ATTR_FORK);
		xfs_inode_verifier_error(ip, -EFSCORRUPTED, "attr fork",
				ifp ? ifp->if_u1.if_data : NULL,
				ifp ? ifp->if_bytes : 0, fa);
		return false;
	}
	return true;
}