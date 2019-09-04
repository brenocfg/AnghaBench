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
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int XFS_COW_FORK ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 scalar_t__ XFS_IFORK_FORMAT (struct xfs_inode*,int) ; 
 scalar_t__ XFS_IFORK_MAXEXT (struct xfs_inode*,int) ; 
 scalar_t__ XFS_IFORK_NEXTENTS (struct xfs_inode*,int) ; 

__attribute__((used)) static inline bool xfs_bmap_wants_extents(struct xfs_inode *ip, int whichfork)
{
	return whichfork != XFS_COW_FORK &&
		XFS_IFORK_FORMAT(ip, whichfork) == XFS_DINODE_FMT_BTREE &&
		XFS_IFORK_NEXTENTS(ip, whichfork) <=
			XFS_IFORK_MAXEXT(ip, whichfork);
}