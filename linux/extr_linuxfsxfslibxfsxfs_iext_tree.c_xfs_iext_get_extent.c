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
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {int dummy; } ;
struct xfs_bmbt_irec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cur_rec (struct xfs_iext_cursor*) ; 
 int /*<<< orphan*/  xfs_iext_get (struct xfs_bmbt_irec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_valid (struct xfs_ifork*,struct xfs_iext_cursor*) ; 

bool
xfs_iext_get_extent(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur,
	struct xfs_bmbt_irec	*gotp)
{
	if (!xfs_iext_valid(ifp, cur))
		return false;
	xfs_iext_get(gotp, cur_rec(cur));
	return true;
}