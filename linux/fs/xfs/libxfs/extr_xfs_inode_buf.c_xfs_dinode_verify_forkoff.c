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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_dev_t ;
struct xfs_mount {int dummy; } ;
struct xfs_dinode {int di_format; int di_forkoff; int /*<<< orphan*/  di_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DFORK_Q (struct xfs_dinode*) ; 
#define  XFS_DINODE_FMT_BTREE 131 
#define  XFS_DINODE_FMT_DEV 130 
#define  XFS_DINODE_FMT_EXTENTS 129 
#define  XFS_DINODE_FMT_LOCAL 128 
 int XFS_LITINO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __this_address ; 
 int roundup (int,int) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dinode_verify_forkoff(
	struct xfs_dinode	*dip,
	struct xfs_mount	*mp)
{
	if (!XFS_DFORK_Q(dip))
		return NULL;

	switch (dip->di_format)  {
	case XFS_DINODE_FMT_DEV:
		if (dip->di_forkoff != (roundup(sizeof(xfs_dev_t), 8) >> 3))
			return __this_address;
		break;
	case XFS_DINODE_FMT_LOCAL:	/* fall through ... */
	case XFS_DINODE_FMT_EXTENTS:    /* fall through ... */
	case XFS_DINODE_FMT_BTREE:
		if (dip->di_forkoff >= (XFS_LITINO(mp, dip->di_version) >> 3))
			return __this_address;
		break;
	default:
		return __this_address;
	}
	return NULL;
}