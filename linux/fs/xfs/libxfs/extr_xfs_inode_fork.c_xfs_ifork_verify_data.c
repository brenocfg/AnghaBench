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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_3__ {scalar_t__ di_format; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct xfs_ifork_ops {int /*<<< orphan*/ * (* verify_symlink ) (struct xfs_inode*) ;int /*<<< orphan*/ * (* verify_dir ) (struct xfs_inode*) ;} ;
struct TYPE_4__ {int i_mode; } ;

/* Variables and functions */
#define  S_IFDIR 129 
#define  S_IFLNK 128 
 int S_IFMT ; 
 TYPE_2__* VFS_I (struct xfs_inode*) ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/ * stub1 (struct xfs_inode*) ; 
 int /*<<< orphan*/ * stub2 (struct xfs_inode*) ; 

xfs_failaddr_t
xfs_ifork_verify_data(
	struct xfs_inode	*ip,
	struct xfs_ifork_ops	*ops)
{
	/* Non-local data fork, we're done. */
	if (ip->i_d.di_format != XFS_DINODE_FMT_LOCAL)
		return NULL;

	/* Check the inline data fork if there is one. */
	switch (VFS_I(ip)->i_mode & S_IFMT) {
	case S_IFDIR:
		return ops->verify_dir(ip);
	case S_IFLNK:
		return ops->verify_symlink(ip);
	default:
		return NULL;
	}
}