#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* i_itemp; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_4__ {int ili_fields; } ;

/* Variables and functions */
 int XFS_ILOG_ALL ; 

__attribute__((used)) static inline int xfs_inode_clean(xfs_inode_t *ip)
{
	return !ip->i_itemp || !(ip->i_itemp->ili_fields & XFS_ILOG_ALL);
}