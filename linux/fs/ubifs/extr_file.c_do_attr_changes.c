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
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 void* timestamp_truncate (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static void do_attr_changes(struct inode *inode, const struct iattr *attr)
{
	if (attr->ia_valid & ATTR_UID)
		inode->i_uid = attr->ia_uid;
	if (attr->ia_valid & ATTR_GID)
		inode->i_gid = attr->ia_gid;
	if (attr->ia_valid & ATTR_ATIME) {
		inode->i_atime = timestamp_truncate(attr->ia_atime,
						  inode);
	}
	if (attr->ia_valid & ATTR_MTIME) {
		inode->i_mtime = timestamp_truncate(attr->ia_mtime,
						  inode);
	}
	if (attr->ia_valid & ATTR_CTIME) {
		inode->i_ctime = timestamp_truncate(attr->ia_ctime,
						  inode);
	}
	if (attr->ia_valid & ATTR_MODE) {
		umode_t mode = attr->ia_mode;

		if (!in_group_p(inode->i_gid) && !capable(CAP_FSETID))
			mode &= ~S_ISGID;
		inode->i_mode = mode;
	}
}