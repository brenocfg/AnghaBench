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
typedef  int xfs_fileoff_t ;
struct xfs_inode {int dummy; } ;
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {int br_startoff; int br_blockcount; } ;

/* Variables and functions */
 scalar_t__ xfs_iext_lookup_extent (struct xfs_inode*,struct xfs_ifork*,int,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_iext_prev_extent (struct xfs_ifork*,struct xfs_iext_cursor*,struct xfs_bmbt_irec*) ; 

bool
xfs_iext_lookup_extent_before(
	struct xfs_inode	*ip,
	struct xfs_ifork	*ifp,
	xfs_fileoff_t		*end,
	struct xfs_iext_cursor	*cur,
	struct xfs_bmbt_irec	*gotp)
{
	/* could be optimized to not even look up the next on a match.. */
	if (xfs_iext_lookup_extent(ip, ifp, *end - 1, cur, gotp) &&
	    gotp->br_startoff <= *end - 1)
		return true;
	if (!xfs_iext_prev_extent(ifp, cur, gotp))
		return false;
	*end = gotp->br_startoff + gotp->br_blockcount;
	return true;
}