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
struct TYPE_2__ {int /*<<< orphan*/  tr_sb; } ;

/* Variables and functions */
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_TRANS_NO_WRITECOUNT ; 
 int /*<<< orphan*/  xfs_log_sb (struct xfs_trans*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

int
xfs_sync_sb(
	struct xfs_mount	*mp,
	bool			wait)
{
	struct xfs_trans	*tp;
	int			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_sb, 0, 0,
			XFS_TRANS_NO_WRITECOUNT, &tp);
	if (error)
		return error;

	xfs_log_sb(tp);
	if (wait)
		xfs_trans_set_sync(tp);
	return xfs_trans_commit(tp);
}