#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct xfs_mount* i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_bmbt_rec_t ;
typedef  int uint ;
struct xfs_mount {int dummy; } ;
struct xfs_ifork {int if_broot_bytes; char* if_broot; int /*<<< orphan*/  if_flags; } ;
typedef  char xfs_btree_block ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 scalar_t__ XFS_BMAP_BMDR_SPACE (char*) ; 
 scalar_t__ XFS_BMAP_BROOT_PTR_ADDR (struct xfs_mount*,char*,int,int) ; 
 size_t XFS_BMAP_BROOT_SPACE_CALC (struct xfs_mount*,int) ; 
 int XFS_BMBT_BLOCK_LEN (struct xfs_mount*) ; 
 scalar_t__ XFS_BMBT_REC_ADDR (struct xfs_mount*,char*,int) ; 
 int /*<<< orphan*/  XFS_IFBROOT ; 
 struct xfs_ifork* XFS_IFORK_PTR (TYPE_1__*,int) ; 
 scalar_t__ XFS_IFORK_SIZE (TYPE_1__*,int) ; 
 void* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*) ; 
 char* kmem_realloc (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int xfs_bmbt_maxrecs (struct xfs_mount*,int,int /*<<< orphan*/ ) ; 

void
xfs_iroot_realloc(
	xfs_inode_t		*ip,
	int			rec_diff,
	int			whichfork)
{
	struct xfs_mount	*mp = ip->i_mount;
	int			cur_max;
	struct xfs_ifork	*ifp;
	struct xfs_btree_block	*new_broot;
	int			new_max;
	size_t			new_size;
	char			*np;
	char			*op;

	/*
	 * Handle the degenerate case quietly.
	 */
	if (rec_diff == 0) {
		return;
	}

	ifp = XFS_IFORK_PTR(ip, whichfork);
	if (rec_diff > 0) {
		/*
		 * If there wasn't any memory allocated before, just
		 * allocate it now and get out.
		 */
		if (ifp->if_broot_bytes == 0) {
			new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, rec_diff);
			ifp->if_broot = kmem_alloc(new_size, KM_NOFS);
			ifp->if_broot_bytes = (int)new_size;
			return;
		}

		/*
		 * If there is already an existing if_broot, then we need
		 * to realloc() it and shift the pointers to their new
		 * location.  The records don't change location because
		 * they are kept butted up against the btree block header.
		 */
		cur_max = xfs_bmbt_maxrecs(mp, ifp->if_broot_bytes, 0);
		new_max = cur_max + rec_diff;
		new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, new_max);
		ifp->if_broot = kmem_realloc(ifp->if_broot, new_size,
				KM_NOFS);
		op = (char *)XFS_BMAP_BROOT_PTR_ADDR(mp, ifp->if_broot, 1,
						     ifp->if_broot_bytes);
		np = (char *)XFS_BMAP_BROOT_PTR_ADDR(mp, ifp->if_broot, 1,
						     (int)new_size);
		ifp->if_broot_bytes = (int)new_size;
		ASSERT(XFS_BMAP_BMDR_SPACE(ifp->if_broot) <=
			XFS_IFORK_SIZE(ip, whichfork));
		memmove(np, op, cur_max * (uint)sizeof(xfs_fsblock_t));
		return;
	}

	/*
	 * rec_diff is less than 0.  In this case, we are shrinking the
	 * if_broot buffer.  It must already exist.  If we go to zero
	 * records, just get rid of the root and clear the status bit.
	 */
	ASSERT((ifp->if_broot != NULL) && (ifp->if_broot_bytes > 0));
	cur_max = xfs_bmbt_maxrecs(mp, ifp->if_broot_bytes, 0);
	new_max = cur_max + rec_diff;
	ASSERT(new_max >= 0);
	if (new_max > 0)
		new_size = XFS_BMAP_BROOT_SPACE_CALC(mp, new_max);
	else
		new_size = 0;
	if (new_size > 0) {
		new_broot = kmem_alloc(new_size, KM_NOFS);
		/*
		 * First copy over the btree block header.
		 */
		memcpy(new_broot, ifp->if_broot,
			XFS_BMBT_BLOCK_LEN(ip->i_mount));
	} else {
		new_broot = NULL;
		ifp->if_flags &= ~XFS_IFBROOT;
	}

	/*
	 * Only copy the records and pointers if there are any.
	 */
	if (new_max > 0) {
		/*
		 * First copy the records.
		 */
		op = (char *)XFS_BMBT_REC_ADDR(mp, ifp->if_broot, 1);
		np = (char *)XFS_BMBT_REC_ADDR(mp, new_broot, 1);
		memcpy(np, op, new_max * (uint)sizeof(xfs_bmbt_rec_t));

		/*
		 * Then copy the pointers.
		 */
		op = (char *)XFS_BMAP_BROOT_PTR_ADDR(mp, ifp->if_broot, 1,
						     ifp->if_broot_bytes);
		np = (char *)XFS_BMAP_BROOT_PTR_ADDR(mp, new_broot, 1,
						     (int)new_size);
		memcpy(np, op, new_max * (uint)sizeof(xfs_fsblock_t));
	}
	kmem_free(ifp->if_broot);
	ifp->if_broot = new_broot;
	ifp->if_broot_bytes = (int)new_size;
	if (ifp->if_broot)
		ASSERT(XFS_BMAP_BMDR_SPACE(ifp->if_broot) <=
			XFS_IFORK_SIZE(ip, whichfork));
	return;
}