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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_btnum_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int xfs_btree_count_blocks (struct xfs_btree_cur*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int) ; 
 int xfs_inobt_cur (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_btree_cur**,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

__attribute__((used)) static int
xfs_inobt_count_blocks(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum,
	xfs_extlen_t		*tree_blocks)
{
	struct xfs_buf		*agbp = NULL;
	struct xfs_btree_cur	*cur = NULL;
	int			error;

	error = xfs_inobt_cur(mp, tp, agno, btnum, &cur, &agbp);
	if (error)
		return error;

	error = xfs_btree_count_blocks(cur, tree_blocks);
	xfs_btree_del_cursor(cur, error);
	xfs_trans_brelse(tp, agbp);

	return error;
}