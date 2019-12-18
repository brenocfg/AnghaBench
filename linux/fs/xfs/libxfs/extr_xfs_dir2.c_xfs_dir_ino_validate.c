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
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  scalar_t__ xfs_ino_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_ERRTAG_DIR_INO_VALIDATE ; 
 int /*<<< orphan*/  XFS_TEST_ERROR (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int xfs_verify_dir_ino (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xfs_warn (int /*<<< orphan*/ *,char*,unsigned long long) ; 

int
xfs_dir_ino_validate(
	xfs_mount_t	*mp,
	xfs_ino_t	ino)
{
	bool		ino_ok = xfs_verify_dir_ino(mp, ino);

	if (unlikely(XFS_TEST_ERROR(!ino_ok, mp, XFS_ERRTAG_DIR_INO_VALIDATE))) {
		xfs_warn(mp, "Invalid inode number 0x%Lx",
				(unsigned long long) ino);
		XFS_ERROR_REPORT("xfs_dir_ino_validate", XFS_ERRLEVEL_LOW, mp);
		return -EFSCORRUPTED;
	}
	return 0;
}