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
struct xfs_scrub {int flags; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XATTR_SIZE_MAX ; 
 int XCHK_TRY_HARDER ; 
 int xchk_setup_inode_contents (struct xfs_scrub*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xchk_setup_xattr_buf (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xchk_setup_xattr(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	int			error;

	/*
	 * We failed to get memory while checking attrs, so this time try to
	 * get all the memory we're ever going to need.  Allocate the buffer
	 * without the inode lock held, which means we can sleep.
	 */
	if (sc->flags & XCHK_TRY_HARDER) {
		error = xchk_setup_xattr_buf(sc, XATTR_SIZE_MAX, 0);
		if (error)
			return error;
	}

	return xchk_setup_inode_contents(sc, ip, 0);
}