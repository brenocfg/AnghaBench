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
struct xfs_trans {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_3__ {struct xfs_buf* agbp; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

void
xfs_rmap_finish_one_cleanup(
	struct xfs_trans	*tp,
	struct xfs_btree_cur	*rcur,
	int			error)
{
	struct xfs_buf		*agbp;

	if (rcur == NULL)
		return;
	agbp = rcur->bc_private.a.agbp;
	xfs_btree_del_cursor(rcur, error);
	if (error)
		xfs_trans_brelse(tp, agbp);
}