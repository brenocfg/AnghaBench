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
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ F2FS_META_INO (int /*<<< orphan*/ ) ; 
 scalar_t__ F2FS_NODE_INO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __ATOMIC_FILE ; 
 int __DIR_FILE ; 
 int __META_FILE ; 
 int __MISC_FILE ; 
 int __NODE_FILE ; 
 int __NORMAL_FILE ; 
 int __VOLATILE_FILE ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_volatile_file (struct inode*) ; 

__attribute__((used)) static int __file_type(struct inode *inode, pid_t pid)
{
	if (f2fs_is_atomic_file(inode))
		return __ATOMIC_FILE;
	else if (f2fs_is_volatile_file(inode))
		return __VOLATILE_FILE;
	else if (S_ISDIR(inode->i_mode))
		return __DIR_FILE;
	else if (inode->i_ino == F2FS_NODE_INO(F2FS_I_SB(inode)))
		return __NODE_FILE;
	else if (inode->i_ino == F2FS_META_INO(F2FS_I_SB(inode)))
		return __META_FILE;
	else if (pid)
		return __NORMAL_FILE;
	else
		return __MISC_FILE;
}