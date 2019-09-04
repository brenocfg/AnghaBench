#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_mount {TYPE_2__* m_ddev_targp; TYPE_1__* m_rtdev_targp; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct inode {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {struct block_device* bt_bdev; } ;
struct TYPE_3__ {struct block_device* bt_bdev; } ;

/* Variables and functions */
 struct xfs_inode* XFS_I (struct inode*) ; 
 scalar_t__ XFS_IS_REALTIME_INODE (struct xfs_inode*) ; 

struct block_device *
xfs_find_bdev_for_inode(
	struct inode		*inode)
{
	struct xfs_inode	*ip = XFS_I(inode);
	struct xfs_mount	*mp = ip->i_mount;

	if (XFS_IS_REALTIME_INODE(ip))
		return mp->m_rtdev_targp->bt_bdev;
	else
		return mp->m_ddev_targp->bt_bdev;
}