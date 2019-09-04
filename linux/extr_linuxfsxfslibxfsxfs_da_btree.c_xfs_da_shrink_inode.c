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
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {int dummy; } ;
struct xfs_da_args {int whichfork; TYPE_1__* geo; struct xfs_trans* trans; struct xfs_inode* dp; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int fsbcount; } ;

/* Variables and functions */
 int ENOSPC ; 
 int XFS_DATA_FORK ; 
 int /*<<< orphan*/  trace_xfs_da_shrink_inode (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_bmapi_aflag (int) ; 
 int xfs_bunmapi (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int xfs_da3_swap_lastblock (struct xfs_da_args*,int /*<<< orphan*/ *,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_binval (struct xfs_trans*,struct xfs_buf*) ; 

int
xfs_da_shrink_inode(
	struct xfs_da_args	*args,
	xfs_dablk_t		dead_blkno,
	struct xfs_buf		*dead_buf)
{
	struct xfs_inode	*dp;
	int			done, error, w, count;
	struct xfs_trans	*tp;

	trace_xfs_da_shrink_inode(args);

	dp = args->dp;
	w = args->whichfork;
	tp = args->trans;
	count = args->geo->fsbcount;
	for (;;) {
		/*
		 * Remove extents.  If we get ENOSPC for a dir we have to move
		 * the last block to the place we want to kill.
		 */
		error = xfs_bunmapi(tp, dp, dead_blkno, count,
				    xfs_bmapi_aflag(w), 0, &done);
		if (error == -ENOSPC) {
			if (w != XFS_DATA_FORK)
				break;
			error = xfs_da3_swap_lastblock(args, &dead_blkno,
						      &dead_buf);
			if (error)
				break;
		} else {
			break;
		}
	}
	xfs_trans_binval(tp, dead_buf);
	return error;
}