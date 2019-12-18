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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fsxattr {int /*<<< orphan*/  fsx_projid; } ;
struct ext4_inode_info {int i_flags; int /*<<< orphan*/  i_projid; } ;

/* Variables and functions */
 int EXT4_FL_USER_VISIBLE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 scalar_t__ ext4_has_feature_project (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_iflags_to_xflags (int) ; 
 int /*<<< orphan*/  from_kprojid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  simple_fill_fsxattr (struct fsxattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_fill_fsxattr(struct inode *inode, struct fsxattr *fa)
{
	struct ext4_inode_info *ei = EXT4_I(inode);

	simple_fill_fsxattr(fa, ext4_iflags_to_xflags(ei->i_flags &
						      EXT4_FL_USER_VISIBLE));

	if (ext4_has_feature_project(inode->i_sb))
		fa->fsx_projid = from_kprojid(&init_user_ns, ei->i_projid);
}