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
struct inode {int /*<<< orphan*/  i_flags; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 long EACCES ; 
 long EPERM ; 
 int /*<<< orphan*/  O_WRONLY ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int S_APPEND ; 
 unsigned int S_IMMUTABLE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 long mnt_want_write_file (struct file*) ; 
 int /*<<< orphan*/  ovl_copyflags (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_real (struct inode*) ; 
 long ovl_maybe_copy_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ovl_real_ioctl (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ovl_ioctl_set_flags(struct file *file, unsigned int cmd,
				unsigned long arg, unsigned int iflags)
{
	long ret;
	struct inode *inode = file_inode(file);
	unsigned int old_iflags;

	if (!inode_owner_or_capable(inode))
		return -EACCES;

	ret = mnt_want_write_file(file);
	if (ret)
		return ret;

	inode_lock(inode);

	/* Check the capability before cred override */
	ret = -EPERM;
	old_iflags = READ_ONCE(inode->i_flags);
	if (((iflags ^ old_iflags) & (S_APPEND | S_IMMUTABLE)) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		goto unlock;

	ret = ovl_maybe_copy_up(file_dentry(file), O_WRONLY);
	if (ret)
		goto unlock;

	ret = ovl_real_ioctl(file, cmd, arg);

	ovl_copyflags(ovl_inode_real(inode), inode);
unlock:
	inode_unlock(inode);

	mnt_drop_write_file(file);

	return ret;

}