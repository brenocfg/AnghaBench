#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_3__ {int /*<<< orphan*/  agno; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 int xfs_verify_agbno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
xfs_btree_check_sptr(
	struct xfs_btree_cur	*cur,
	xfs_agblock_t		agbno,
	int			level)
{
	if (level <= 0)
		return false;
	return xfs_verify_agbno(cur->bc_mp, cur->bc_private.a.agno, agbno);
}