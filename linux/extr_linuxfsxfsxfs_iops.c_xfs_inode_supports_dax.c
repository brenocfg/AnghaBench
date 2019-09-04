#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sb_blocksize; } ;
struct xfs_mount {int m_flags; TYPE_2__ m_sb; } ;
struct TYPE_5__ {int di_flags2; } ;
struct xfs_inode {TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_3__* VFS_I (struct xfs_inode*) ; 
 int XFS_DIFLAG2_DAX ; 
 int XFS_MOUNT_DAX ; 
 int /*<<< orphan*/ * xfs_find_daxdev_for_inode (TYPE_3__*) ; 
 scalar_t__ xfs_is_reflink_inode (struct xfs_inode*) ; 

__attribute__((used)) static bool
xfs_inode_supports_dax(
	struct xfs_inode	*ip)
{
	struct xfs_mount	*mp = ip->i_mount;

	/* Only supported on non-reflinked files. */
	if (!S_ISREG(VFS_I(ip)->i_mode) || xfs_is_reflink_inode(ip))
		return false;

	/* DAX mount option or DAX iflag must be set. */
	if (!(mp->m_flags & XFS_MOUNT_DAX) &&
	    !(ip->i_d.di_flags2 & XFS_DIFLAG2_DAX))
		return false;

	/* Block size must match page size */
	if (mp->m_sb.sb_blocksize != PAGE_SIZE)
		return false;

	/* Device has to support DAX too. */
	return xfs_find_daxdev_for_inode(VFS_I(ip)) != NULL;
}