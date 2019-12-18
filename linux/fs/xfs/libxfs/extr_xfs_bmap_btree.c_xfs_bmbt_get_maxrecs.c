#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_ifork {int /*<<< orphan*/  if_broot_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  whichfork; int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {TYPE_1__ b; } ;
struct xfs_btree_cur {int bc_nlevels; TYPE_3__* bc_mp; TYPE_2__ bc_private; } ;
struct TYPE_6__ {int* m_bmap_dmxr; } ;

/* Variables and functions */
 struct xfs_ifork* XFS_IFORK_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_bmbt_maxrecs (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int
xfs_bmbt_get_maxrecs(
	struct xfs_btree_cur	*cur,
	int			level)
{
	if (level == cur->bc_nlevels - 1) {
		struct xfs_ifork	*ifp;

		ifp = XFS_IFORK_PTR(cur->bc_private.b.ip,
				    cur->bc_private.b.whichfork);

		return xfs_bmbt_maxrecs(cur->bc_mp,
					ifp->if_broot_bytes, level == 0);
	}

	return cur->bc_mp->m_bmap_dmxr[level != 0];

}