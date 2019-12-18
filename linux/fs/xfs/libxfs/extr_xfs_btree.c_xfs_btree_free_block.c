#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int /*<<< orphan*/  bc_tp; TYPE_1__* bc_ops; } ;
struct TYPE_2__ {int (* free_block ) (struct xfs_btree_cur*,struct xfs_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_STATS_INC (struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 int stub1 (struct xfs_btree_cur*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_binval (int /*<<< orphan*/ ,struct xfs_buf*) ; 

__attribute__((used)) static int
xfs_btree_free_block(
	struct xfs_btree_cur	*cur,
	struct xfs_buf		*bp)
{
	int			error;

	error = cur->bc_ops->free_block(cur, bp);
	if (!error) {
		xfs_trans_binval(cur->bc_tp, bp);
		XFS_BTREE_STATS_INC(cur, free);
	}
	return error;
}