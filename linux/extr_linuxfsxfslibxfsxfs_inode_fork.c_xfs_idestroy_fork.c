#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * i_cowfp; int /*<<< orphan*/ * i_afp; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_6__ {int /*<<< orphan*/ * if_data; } ;
struct xfs_ifork {int if_flags; scalar_t__ if_height; TYPE_1__ if_u1; int /*<<< orphan*/ * if_broot; } ;

/* Variables and functions */
 int XFS_ATTR_FORK ; 
 int XFS_COW_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int XFS_IFEXTENTS ; 
 scalar_t__ XFS_IFORK_FORMAT (TYPE_2__*,int) ; 
 struct xfs_ifork* XFS_IFORK_PTR (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_iext_destroy (struct xfs_ifork*) ; 
 int /*<<< orphan*/  xfs_ifork_zone ; 

void
xfs_idestroy_fork(
	xfs_inode_t	*ip,
	int		whichfork)
{
	struct xfs_ifork	*ifp;

	ifp = XFS_IFORK_PTR(ip, whichfork);
	if (ifp->if_broot != NULL) {
		kmem_free(ifp->if_broot);
		ifp->if_broot = NULL;
	}

	/*
	 * If the format is local, then we can't have an extents
	 * array so just look for an inline data array.  If we're
	 * not local then we may or may not have an extents list,
	 * so check and free it up if we do.
	 */
	if (XFS_IFORK_FORMAT(ip, whichfork) == XFS_DINODE_FMT_LOCAL) {
		if (ifp->if_u1.if_data != NULL) {
			kmem_free(ifp->if_u1.if_data);
			ifp->if_u1.if_data = NULL;
		}
	} else if ((ifp->if_flags & XFS_IFEXTENTS) && ifp->if_height) {
		xfs_iext_destroy(ifp);
	}

	if (whichfork == XFS_ATTR_FORK) {
		kmem_zone_free(xfs_ifork_zone, ip->i_afp);
		ip->i_afp = NULL;
	} else if (whichfork == XFS_COW_FORK) {
		kmem_zone_free(xfs_ifork_zone, ip->i_cowfp);
		ip->i_cowfp = NULL;
	}
}