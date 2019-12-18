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
struct xfs_scrub {int /*<<< orphan*/  buf; struct xfs_inode* ip; } ;
struct TYPE_4__ {scalar_t__ di_size; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_data; } ;
struct xfs_ifork {int if_flags; TYPE_2__ if_u1; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 TYPE_3__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_IFINLINE ; 
 scalar_t__ XFS_IFORK_DSIZE (struct xfs_inode*) ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_SYMLINK_MAXLEN ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xchk_fblock_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xchk_fblock_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_readlink_bmap_ilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xchk_symlink(
	struct xfs_scrub	*sc)
{
	struct xfs_inode	*ip = sc->ip;
	struct xfs_ifork	*ifp;
	loff_t			len;
	int			error = 0;

	if (!S_ISLNK(VFS_I(ip)->i_mode))
		return -ENOENT;
	ifp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	len = ip->i_d.di_size;

	/* Plausible size? */
	if (len > XFS_SYMLINK_MAXLEN || len <= 0) {
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		goto out;
	}

	/* Inline symlink? */
	if (ifp->if_flags & XFS_IFINLINE) {
		if (len > XFS_IFORK_DSIZE(ip) ||
		    len > strnlen(ifp->if_u1.if_data, XFS_IFORK_DSIZE(ip)))
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		goto out;
	}

	/* Remote symlink; must read the contents. */
	error = xfs_readlink_bmap_ilocked(sc->ip, sc->buf);
	if (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		goto out;
	if (strnlen(sc->buf, XFS_SYMLINK_MAXLEN) < len)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
out:
	return error;
}