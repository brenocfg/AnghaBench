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
struct xfs_trans_res {int /*<<< orphan*/  tr_logflags; int /*<<< orphan*/  tr_logcount; int /*<<< orphan*/  tr_logres; } ;
struct xfs_trans {int /*<<< orphan*/  t_log_count; int /*<<< orphan*/  t_log_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int __xfs_trans_commit (struct xfs_trans*,int) ; 
 int /*<<< orphan*/  trace_xfs_trans_roll (struct xfs_trans*,int /*<<< orphan*/ ) ; 
 struct xfs_trans* xfs_trans_dup (struct xfs_trans*) ; 
 int xfs_trans_reserve (struct xfs_trans*,struct xfs_trans_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_trans_roll(
	struct xfs_trans	**tpp)
{
	struct xfs_trans	*trans = *tpp;
	struct xfs_trans_res	tres;
	int			error;

	trace_xfs_trans_roll(trans, _RET_IP_);

	/*
	 * Copy the critical parameters from one trans to the next.
	 */
	tres.tr_logres = trans->t_log_res;
	tres.tr_logcount = trans->t_log_count;

	*tpp = xfs_trans_dup(trans);

	/*
	 * Commit the current transaction.
	 * If this commit failed, then it'd just unlock those items that
	 * are not marked ihold. That also means that a filesystem shutdown
	 * is in progress. The caller takes the responsibility to cancel
	 * the duplicate transaction that gets returned.
	 */
	error = __xfs_trans_commit(trans, true);
	if (error)
		return error;

	/*
	 * Reserve space in the log for the next transaction.
	 * This also pushes items in the "AIL", the list of logged items,
	 * out to disk if they are taking up space at the tail of the log
	 * that we want to use.  This requires that either nothing be locked
	 * across this call, or that anything that is locked be logged in
	 * the prior and the next transactions.
	 */
	tres.tr_logflags = XFS_TRANS_PERM_LOG_RES;
	return xfs_trans_reserve(*tpp, &tres, 0, 0);
}