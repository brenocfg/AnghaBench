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
struct xfs_ifork {int /*<<< orphan*/  if_bytes; } ;

/* Variables and functions */
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_IFORK_FORMAT (struct xfs_inode*,int) ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_idata_realloc (struct xfs_inode*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
xfs_ifree_local_data(
	struct xfs_inode	*ip,
	int			whichfork)
{
	struct xfs_ifork	*ifp;

	if (XFS_IFORK_FORMAT(ip, whichfork) != XFS_DINODE_FMT_LOCAL)
		return;

	ifp = XFS_IFORK_PTR(ip, whichfork);
	xfs_idata_realloc(ip, -ifp->if_bytes, whichfork);
}