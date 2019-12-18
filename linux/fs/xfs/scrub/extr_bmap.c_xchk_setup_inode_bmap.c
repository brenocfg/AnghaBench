#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_scrub {int ilock_flags; int /*<<< orphan*/  ip; TYPE_1__* sm; } ;
struct xfs_inode {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {scalar_t__ sm_type; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_2__* VFS_I (int /*<<< orphan*/ ) ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_IOLOCK_EXCL ; 
 int XFS_MMAPLOCK_EXCL ; 
 scalar_t__ XFS_SCRUB_TYPE_BMBTD ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_dio_wait (TYPE_2__*) ; 
 int xchk_get_inode (struct xfs_scrub*,struct xfs_inode*) ; 
 int xchk_trans_alloc (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (int /*<<< orphan*/ ,int) ; 

int
xchk_setup_inode_bmap(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	int			error;

	error = xchk_get_inode(sc, ip);
	if (error)
		goto out;

	sc->ilock_flags = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);

	/*
	 * We don't want any ephemeral data fork updates sitting around
	 * while we inspect block mappings, so wait for directio to finish
	 * and flush dirty data if we have delalloc reservations.
	 */
	if (S_ISREG(VFS_I(sc->ip)->i_mode) &&
	    sc->sm->sm_type == XFS_SCRUB_TYPE_BMBTD) {
		inode_dio_wait(VFS_I(sc->ip));
		error = filemap_write_and_wait(VFS_I(sc->ip)->i_mapping);
		if (error)
			goto out;
	}

	/* Got the inode, lock it and we're ready to go. */
	error = xchk_trans_alloc(sc, 0);
	if (error)
		goto out;
	sc->ilock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);

out:
	/* scrub teardown will unlock and release the inode */
	return error;
}