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
struct TYPE_3__ {int /*<<< orphan*/  agno; int /*<<< orphan*/  agbp; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; int /*<<< orphan*/  bc_tp; int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 struct xfs_btree_cur* xfs_rmapbt_init_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfs_btree_cur *
xfs_rmapbt_dup_cursor(
	struct xfs_btree_cur	*cur)
{
	return xfs_rmapbt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_private.a.agbp, cur->bc_private.a.agno);
}