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
struct TYPE_2__ {int /*<<< orphan*/  di_flags2; } ;
struct xfs_inode {TYPE_1__ i_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULLFILEOFF ; 
 int /*<<< orphan*/  XFS_DIFLAG2_REFLINK ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  trace_xfs_reflink_unset_inode_flag (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_inode_clear_cowblocks_tag (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_is_reflink_inode (struct xfs_inode*) ; 
 int xfs_reflink_cancel_cow_blocks (struct xfs_inode*,struct xfs_trans**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xfs_reflink_inode_has_shared_extents (struct xfs_trans*,struct xfs_inode*,int*) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xfs_reflink_clear_inode_flag(
	struct xfs_inode	*ip,
	struct xfs_trans	**tpp)
{
	bool			needs_flag;
	int			error = 0;

	ASSERT(xfs_is_reflink_inode(ip));

	error = xfs_reflink_inode_has_shared_extents(*tpp, ip, &needs_flag);
	if (error || needs_flag)
		return error;

	/*
	 * We didn't find any shared blocks so turn off the reflink flag.
	 * First, get rid of any leftover CoW mappings.
	 */
	error = xfs_reflink_cancel_cow_blocks(ip, tpp, 0, NULLFILEOFF, true);
	if (error)
		return error;

	/* Clear the inode flag. */
	trace_xfs_reflink_unset_inode_flag(ip);
	ip->i_d.di_flags2 &= ~XFS_DIFLAG2_REFLINK;
	xfs_inode_clear_cowblocks_tag(ip);
	xfs_trans_log_inode(*tpp, ip, XFS_ILOG_CORE);

	return error;
}