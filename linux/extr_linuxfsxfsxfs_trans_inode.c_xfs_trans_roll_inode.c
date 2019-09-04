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
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll (struct xfs_trans**) ; 

int
xfs_trans_roll_inode(
	struct xfs_trans	**tpp,
	struct xfs_inode	*ip)
{
	int			error;

	xfs_trans_log_inode(*tpp, ip, XFS_ILOG_CORE);
	error = xfs_trans_roll(tpp);
	if (!error)
		xfs_trans_ijoin(*tpp, ip, 0);
	return error;
}