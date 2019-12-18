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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_FSB_TO_BB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IS_REALTIME_INODE (struct xfs_inode*) ; 

xfs_daddr_t
xfs_fsb_to_db(struct xfs_inode *ip, xfs_fsblock_t fsb)
{
	if (XFS_IS_REALTIME_INODE(ip))
		return XFS_FSB_TO_BB(ip->i_mount, fsb);
	return XFS_FSB_TO_DADDR(ip->i_mount, fsb);
}