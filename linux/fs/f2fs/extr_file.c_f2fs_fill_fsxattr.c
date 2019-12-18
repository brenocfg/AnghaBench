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
struct inode {int dummy; } ;
struct fsxattr {int /*<<< orphan*/  fsx_projid; } ;
struct f2fs_inode_info {int /*<<< orphan*/  i_projid; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  f2fs_iflags_to_xflags (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_sb_has_project_quota (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kprojid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  simple_fill_fsxattr (struct fsxattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_fill_fsxattr(struct inode *inode, struct fsxattr *fa)
{
	struct f2fs_inode_info *fi = F2FS_I(inode);

	simple_fill_fsxattr(fa, f2fs_iflags_to_xflags(fi->i_flags));

	if (f2fs_sb_has_project_quota(F2FS_I_SB(inode)))
		fa->fsx_projid = from_kprojid(&init_user_ns, fi->i_projid);
}