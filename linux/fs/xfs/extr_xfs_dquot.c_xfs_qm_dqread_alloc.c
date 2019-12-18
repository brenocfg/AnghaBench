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
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_dquot {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_qm_dqalloc; } ;

/* Variables and functions */
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_QM_DQALLOC_SPACE_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int xfs_dquot_disk_alloc (struct xfs_trans**,struct xfs_dquot*,struct xfs_buf**) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 

__attribute__((used)) static int
xfs_qm_dqread_alloc(
	struct xfs_mount	*mp,
	struct xfs_dquot	*dqp,
	struct xfs_buf		**bpp)
{
	struct xfs_trans	*tp;
	int			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_dqalloc,
			XFS_QM_DQALLOC_SPACE_RES(mp), 0, 0, &tp);
	if (error)
		goto err;

	error = xfs_dquot_disk_alloc(&tp, dqp, bpp);
	if (error)
		goto err_cancel;

	error = xfs_trans_commit(tp);
	if (error) {
		/*
		 * Buffer was held to the transaction, so we have to unlock it
		 * manually here because we're not passing it back.
		 */
		xfs_buf_relse(*bpp);
		*bpp = NULL;
		goto err;
	}
	return 0;

err_cancel:
	xfs_trans_cancel(tp);
err:
	return error;
}