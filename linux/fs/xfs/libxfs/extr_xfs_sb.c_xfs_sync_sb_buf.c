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
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_sb; } ;

/* Variables and functions */
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int xfs_bwrite (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_log_sb (struct xfs_trans*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_bhold (struct xfs_trans*,struct xfs_buf*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 struct xfs_buf* xfs_trans_getsb (struct xfs_trans*,struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

int
xfs_sync_sb_buf(
	struct xfs_mount	*mp)
{
	struct xfs_trans	*tp;
	struct xfs_buf		*bp;
	int			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_sb, 0, 0, 0, &tp);
	if (error)
		return error;

	bp = xfs_trans_getsb(tp, mp);
	xfs_log_sb(tp);
	xfs_trans_bhold(tp, bp);
	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);
	if (error)
		goto out;
	/*
	 * write out the sb buffer to get the changes to disk
	 */
	error = xfs_bwrite(bp);
out:
	xfs_buf_relse(bp);
	return error;
}