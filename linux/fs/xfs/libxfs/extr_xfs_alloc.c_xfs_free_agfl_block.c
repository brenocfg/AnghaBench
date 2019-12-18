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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_owner_info {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_AG_RESV_AGFL ; 
 struct xfs_buf* xfs_btree_get_bufs (int /*<<< orphan*/ ,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_free_ag_extent (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_owner_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_binval (struct xfs_trans*,struct xfs_buf*) ; 

int
xfs_free_agfl_block(
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	struct xfs_buf		*agbp,
	struct xfs_owner_info	*oinfo)
{
	int			error;
	struct xfs_buf		*bp;

	error = xfs_free_ag_extent(tp, agbp, agno, agbno, 1, oinfo,
				   XFS_AG_RESV_AGFL);
	if (error)
		return error;

	bp = xfs_btree_get_bufs(tp->t_mountp, tp, agno, agbno);
	if (!bp)
		return -EFSCORRUPTED;
	xfs_trans_binval(tp, bp);

	return 0;
}