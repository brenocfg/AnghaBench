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
typedef  int umode_t ;
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSETID ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int S_IXGRP ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 

void inode_init_owner(struct inode *inode, const struct inode *dir,
			umode_t mode)
{
	inode->i_uid = current_fsuid();
	if (dir && dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;

		/* Directories are special, and always inherit S_ISGID */
		if (S_ISDIR(mode))
			mode |= S_ISGID;
		else if ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP) &&
			 !in_group_p(inode->i_gid) &&
			 !capable_wrt_inode_uidgid(dir, CAP_FSETID))
			mode &= ~S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;
}