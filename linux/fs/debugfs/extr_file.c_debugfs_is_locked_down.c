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
struct inode {int i_mode; } ;
struct file_operations {int /*<<< orphan*/  mmap; int /*<<< orphan*/  compat_ioctl; int /*<<< orphan*/  unlocked_ioctl; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  LOCKDOWN_DEBUGFS ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool debugfs_is_locked_down(struct inode *inode,
				   struct file *filp,
				   const struct file_operations *real_fops)
{
	if ((inode->i_mode & 07777) == 0444 &&
	    !(filp->f_mode & FMODE_WRITE) &&
	    !real_fops->unlocked_ioctl &&
	    !real_fops->compat_ioctl &&
	    !real_fops->mmap)
		return false;

	return security_locked_down(LOCKDOWN_DEBUGFS);
}