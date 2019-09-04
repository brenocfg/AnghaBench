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
struct xfs_scrub {int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  XFS_COW_FORK ; 
 int xchk_bmap (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_is_reflink_inode (int /*<<< orphan*/ ) ; 

int
xchk_bmap_cow(
	struct xfs_scrub	*sc)
{
	if (!xfs_is_reflink_inode(sc->ip))
		return -ENOENT;

	return xchk_bmap(sc, XFS_COW_FORK);
}