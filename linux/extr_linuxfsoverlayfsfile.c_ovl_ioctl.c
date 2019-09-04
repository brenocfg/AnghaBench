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
struct file {int dummy; } ;

/* Variables and functions */
 long EACCES ; 
 long ENOTTY ; 
#define  FS_IOC_GETFLAGS 129 
#define  FS_IOC_SETFLAGS 128 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 long mnt_want_write_file (struct file*) ; 
 long ovl_copy_up_with_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_copyflags (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_real (struct inode*) ; 
 long ovl_real_ioctl (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ovl_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;
	struct inode *inode = file_inode(file);

	switch (cmd) {
	case FS_IOC_GETFLAGS:
		ret = ovl_real_ioctl(file, cmd, arg);
		break;

	case FS_IOC_SETFLAGS:
		if (!inode_owner_or_capable(inode))
			return -EACCES;

		ret = mnt_want_write_file(file);
		if (ret)
			return ret;

		ret = ovl_copy_up_with_data(file_dentry(file));
		if (!ret) {
			ret = ovl_real_ioctl(file, cmd, arg);

			inode_lock(inode);
			ovl_copyflags(ovl_inode_real(inode), inode);
			inode_unlock(inode);
		}

		mnt_drop_write_file(file);
		break;

	default:
		ret = -ENOTTY;
	}

	return ret;
}