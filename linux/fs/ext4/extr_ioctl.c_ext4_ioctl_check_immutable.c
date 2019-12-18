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
struct ext4_inode_info {unsigned int i_flags; int /*<<< orphan*/  i_projid; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EPERM ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 unsigned int EXT4_IMMUTABLE_FL ; 
 scalar_t__ __kprojid_val (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_has_feature_project (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_ioctl_check_immutable(struct inode *inode, __u32 new_projid,
				      unsigned int flags)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	unsigned int oldflags = ei->i_flags;

	if (!(oldflags & EXT4_IMMUTABLE_FL) || !(flags & EXT4_IMMUTABLE_FL))
		return 0;

	if ((oldflags & ~EXT4_IMMUTABLE_FL) != (flags & ~EXT4_IMMUTABLE_FL))
		return -EPERM;
	if (ext4_has_feature_project(inode->i_sb) &&
	    __kprojid_val(ei->i_projid) != new_projid)
		return -EPERM;

	return 0;
}