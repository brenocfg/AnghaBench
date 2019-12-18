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
struct xfs_trans {int dummy; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int xfs_bmbt_change_owner (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll (struct xfs_trans**) ; 

__attribute__((used)) static int
xfs_swap_change_owner(
	struct xfs_trans	**tpp,
	struct xfs_inode	*ip,
	struct xfs_inode	*tmpip)
{
	int			error;
	struct xfs_trans	*tp = *tpp;

	do {
		error = xfs_bmbt_change_owner(tp, ip, XFS_DATA_FORK, ip->i_ino,
					      NULL);
		/* success or fatal error */
		if (error != -EAGAIN)
			break;

		error = xfs_trans_roll(tpp);
		if (error)
			break;
		tp = *tpp;

		/*
		 * Redirty both inodes so they can relog and keep the log tail
		 * moving forward.
		 */
		xfs_trans_ijoin(tp, ip, 0);
		xfs_trans_ijoin(tp, tmpip, 0);
		xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
		xfs_trans_log_inode(tp, tmpip, XFS_ILOG_CORE);
	} while (true);

	return error;
}