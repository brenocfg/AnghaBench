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
struct xfs_inode {scalar_t__ i_cnextents; int /*<<< orphan*/  i_cformat; TYPE_1__* i_cowfp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_DINODE_FMT_EXTENTS ; 
 int /*<<< orphan*/  XFS_IFEXTENTS ; 
 TYPE_1__* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ifork_zone ; 

void
xfs_ifork_init_cow(
	struct xfs_inode	*ip)
{
	if (ip->i_cowfp)
		return;

	ip->i_cowfp = kmem_zone_zalloc(xfs_ifork_zone,
				       KM_NOFS);
	ip->i_cowfp->if_flags = XFS_IFEXTENTS;
	ip->i_cformat = XFS_DINODE_FMT_EXTENTS;
	ip->i_cnextents = 0;
}