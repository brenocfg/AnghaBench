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
struct ocfs2_super {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int GROUP_QUOTA_SYSTEM_INODE ; 
 int LOCAL_GROUP_QUOTA_SYSTEM_INODE ; 
 int LOCAL_USER_QUOTA_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_FEATURE_RO_COMPAT_GRPQUOTA ; 
 int /*<<< orphan*/  OCFS2_FEATURE_RO_COMPAT_USRQUOTA ; 
 int /*<<< orphan*/  OCFS2_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USER_QUOTA_SYSTEM_INODE ; 

__attribute__((used)) static int ocfs2_need_system_inode(struct ocfs2_super *osb, int ino)
{
	if (!OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb, OCFS2_FEATURE_RO_COMPAT_USRQUOTA)
	    && (ino == USER_QUOTA_SYSTEM_INODE
		|| ino == LOCAL_USER_QUOTA_SYSTEM_INODE))
		return 0;
	if (!OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb, OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)
	    && (ino == GROUP_QUOTA_SYSTEM_INODE
		|| ino == LOCAL_GROUP_QUOTA_SYSTEM_INODE))
		return 0;
	return 1;
}