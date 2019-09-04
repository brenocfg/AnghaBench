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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
struct xfs_btree_cur {int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 int xfs_verify_fsbno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
xfs_btree_check_lptr(
	struct xfs_btree_cur	*cur,
	xfs_fsblock_t		fsbno,
	int			level)
{
	if (level <= 0)
		return false;
	return xfs_verify_fsbno(cur->bc_mp, fsbno);
}