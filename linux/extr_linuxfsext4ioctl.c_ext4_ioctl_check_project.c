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
struct inode {int dummy; } ;
struct fsxattr {scalar_t__ fsx_projid; int fsx_xflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_projid; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_PROJINHERIT ; 
 int FS_XFLAG_PROJINHERIT ; 
 scalar_t__ __kprojid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_user_ns () ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int ext4_ioctl_check_project(struct inode *inode, struct fsxattr *fa)
{
	/*
	 * Project Quota ID state is only allowed to change from within the init
	 * namespace. Enforce that restriction only if we are trying to change
	 * the quota ID state. Everything else is allowed in user namespaces.
	 */
	if (current_user_ns() == &init_user_ns)
		return 0;

	if (__kprojid_val(EXT4_I(inode)->i_projid) != fa->fsx_projid)
		return -EINVAL;

	if (ext4_test_inode_flag(inode, EXT4_INODE_PROJINHERIT)) {
		if (!(fa->fsx_xflags & FS_XFLAG_PROJINHERIT))
			return -EINVAL;
	} else {
		if (fa->fsx_xflags & FS_XFLAG_PROJINHERIT)
			return -EINVAL;
	}

	return 0;
}