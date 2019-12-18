#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int i_mode; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ likely (int) ; 
 int sysctl_protected_fifos ; 
 int sysctl_protected_regular ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int may_create_in_sticky(struct dentry * const dir,
				struct inode * const inode)
{
	if ((!sysctl_protected_fifos && S_ISFIFO(inode->i_mode)) ||
	    (!sysctl_protected_regular && S_ISREG(inode->i_mode)) ||
	    likely(!(dir->d_inode->i_mode & S_ISVTX)) ||
	    uid_eq(inode->i_uid, dir->d_inode->i_uid) ||
	    uid_eq(current_fsuid(), inode->i_uid))
		return 0;

	if (likely(dir->d_inode->i_mode & 0002) ||
	    (dir->d_inode->i_mode & 0020 &&
	     ((sysctl_protected_fifos >= 2 && S_ISFIFO(inode->i_mode)) ||
	      (sysctl_protected_regular >= 2 && S_ISREG(inode->i_mode))))) {
		return -EACCES;
	}
	return 0;
}