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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_uid; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 void* timestamp_truncate (int /*<<< orphan*/ ,struct inode*) ; 

void setattr_copy(struct inode *inode, const struct iattr *attr)
{
	unsigned int ia_valid = attr->ia_valid;

	if (ia_valid & ATTR_UID)
		inode->i_uid = attr->ia_uid;
	if (ia_valid & ATTR_GID)
		inode->i_gid = attr->ia_gid;
	if (ia_valid & ATTR_ATIME) {
		inode->i_atime = timestamp_truncate(attr->ia_atime,
						  inode);
	}
	if (ia_valid & ATTR_MTIME) {
		inode->i_mtime = timestamp_truncate(attr->ia_mtime,
						  inode);
	}
	if (ia_valid & ATTR_CTIME) {
		inode->i_ctime = timestamp_truncate(attr->ia_ctime,
						  inode);
	}
	if (ia_valid & ATTR_MODE) {
		umode_t mode = attr->ia_mode;

		if (!in_group_p(inode->i_gid) &&
		    !capable_wrt_inode_uidgid(inode, CAP_FSETID))
			mode &= ~S_ISGID;
		inode->i_mode = mode;
	}
}