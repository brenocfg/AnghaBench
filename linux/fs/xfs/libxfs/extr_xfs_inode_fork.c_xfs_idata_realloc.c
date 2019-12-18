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
struct xfs_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * if_data; } ;
struct xfs_ifork {int if_bytes; TYPE_1__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int) ; 
 int XFS_IFORK_SIZE (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int,int) ; 

void
xfs_idata_realloc(
	struct xfs_inode	*ip,
	int			byte_diff,
	int			whichfork)
{
	struct xfs_ifork	*ifp = XFS_IFORK_PTR(ip, whichfork);
	int			new_size = (int)ifp->if_bytes + byte_diff;

	ASSERT(new_size >= 0);
	ASSERT(new_size <= XFS_IFORK_SIZE(ip, whichfork));

	if (byte_diff == 0)
		return;

	if (new_size == 0) {
		kmem_free(ifp->if_u1.if_data);
		ifp->if_u1.if_data = NULL;
		ifp->if_bytes = 0;
		return;
	}

	/*
	 * For inline data, the underlying buffer must be a multiple of 4 bytes
	 * in size so that it can be logged and stay on word boundaries.
	 * We enforce that here.
	 */
	ifp->if_u1.if_data = kmem_realloc(ifp->if_u1.if_data,
			roundup(new_size, 4), KM_NOFS);
	ifp->if_bytes = new_size;
}