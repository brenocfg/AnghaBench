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
struct inode {int /*<<< orphan*/  i_gid; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_mode; void* ia_ctime; void* ia_mtime; void* ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {int /*<<< orphan*/  s_mode; struct iattr* s_iattr; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 void* current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 struct iattr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int simple_setattr (struct dentry*,struct iattr*) ; 
 void* timestamp_truncate (void*,struct inode*) ; 

int configfs_setattr(struct dentry * dentry, struct iattr * iattr)
{
	struct inode * inode = d_inode(dentry);
	struct configfs_dirent * sd = dentry->d_fsdata;
	struct iattr * sd_iattr;
	unsigned int ia_valid = iattr->ia_valid;
	int error;

	if (!sd)
		return -EINVAL;

	sd_iattr = sd->s_iattr;
	if (!sd_iattr) {
		/* setting attributes for the first time, allocate now */
		sd_iattr = kzalloc(sizeof(struct iattr), GFP_KERNEL);
		if (!sd_iattr)
			return -ENOMEM;
		/* assign default attributes */
		sd_iattr->ia_mode = sd->s_mode;
		sd_iattr->ia_uid = GLOBAL_ROOT_UID;
		sd_iattr->ia_gid = GLOBAL_ROOT_GID;
		sd_iattr->ia_atime = sd_iattr->ia_mtime =
			sd_iattr->ia_ctime = current_time(inode);
		sd->s_iattr = sd_iattr;
	}
	/* attributes were changed atleast once in past */

	error = simple_setattr(dentry, iattr);
	if (error)
		return error;

	if (ia_valid & ATTR_UID)
		sd_iattr->ia_uid = iattr->ia_uid;
	if (ia_valid & ATTR_GID)
		sd_iattr->ia_gid = iattr->ia_gid;
	if (ia_valid & ATTR_ATIME)
		sd_iattr->ia_atime = timestamp_truncate(iattr->ia_atime,
						      inode);
	if (ia_valid & ATTR_MTIME)
		sd_iattr->ia_mtime = timestamp_truncate(iattr->ia_mtime,
						      inode);
	if (ia_valid & ATTR_CTIME)
		sd_iattr->ia_ctime = timestamp_truncate(iattr->ia_ctime,
						      inode);
	if (ia_valid & ATTR_MODE) {
		umode_t mode = iattr->ia_mode;

		if (!in_group_p(inode->i_gid) && !capable(CAP_FSETID))
			mode &= ~S_ISGID;
		sd_iattr->ia_mode = sd->s_mode = mode;
	}

	return error;
}