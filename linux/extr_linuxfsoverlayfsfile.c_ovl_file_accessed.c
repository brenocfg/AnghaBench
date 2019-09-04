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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct file {int f_flags; int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int O_NOATIME ; 
 struct inode* file_inode (struct file*) ; 
 struct inode* ovl_inode_upper (struct inode*) ; 
 int /*<<< orphan*/  timespec64_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_atime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ovl_file_accessed(struct file *file)
{
	struct inode *inode, *upperinode;

	if (file->f_flags & O_NOATIME)
		return;

	inode = file_inode(file);
	upperinode = ovl_inode_upper(inode);

	if (!upperinode)
		return;

	if ((!timespec64_equal(&inode->i_mtime, &upperinode->i_mtime) ||
	     !timespec64_equal(&inode->i_ctime, &upperinode->i_ctime))) {
		inode->i_mtime = upperinode->i_mtime;
		inode->i_ctime = upperinode->i_ctime;
	}

	touch_atime(&file->f_path);
}