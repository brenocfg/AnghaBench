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
struct TYPE_4__ {int di_flags; } ;
struct xfs_inode {TYPE_2__ i_d; TYPE_1__* i_mount; } ;
struct TYPE_3__ {int m_flags; } ;

/* Variables and functions */
 int XFS_DIFLAG_FILESTREAM ; 
 int XFS_MOUNT_FILESTREAMS ; 

__attribute__((used)) static inline int
xfs_inode_is_filestream(
	struct xfs_inode	*ip)
{
	return (ip->i_mount->m_flags & XFS_MOUNT_FILESTREAMS) ||
		(ip->i_d.di_flags & XFS_DIFLAG_FILESTREAM);
}