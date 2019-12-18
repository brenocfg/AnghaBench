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
struct xfs_scrub {int ilock_flags; int /*<<< orphan*/  ip; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int XFS_ILOCK_EXCL ; 
 int XFS_IOLOCK_EXCL ; 
 int XFS_MMAPLOCK_EXCL ; 
 int xchk_get_inode (struct xfs_scrub*,struct xfs_inode*) ; 
 int xchk_trans_alloc (struct xfs_scrub*,unsigned int) ; 
 int /*<<< orphan*/  xfs_ilock (int /*<<< orphan*/ ,int) ; 

int
xchk_setup_inode_contents(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip,
	unsigned int		resblks)
{
	int			error;

	error = xchk_get_inode(sc, ip);
	if (error)
		return error;

	/* Got the inode, lock it and we're ready to go. */
	sc->ilock_flags = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);
	error = xchk_trans_alloc(sc, resblks);
	if (error)
		goto out;
	sc->ilock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);

out:
	/* scrub teardown will unlock and release the inode for us */
	return error;
}