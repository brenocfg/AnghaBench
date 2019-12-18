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
 long autofs_root_ioctl_unlocked (struct inode*,struct file*,unsigned int,unsigned long) ; 
 struct inode* file_inode (struct file*) ; 

__attribute__((used)) static long autofs_root_ioctl(struct file *filp,
			       unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file_inode(filp);

	return autofs_root_ioctl_unlocked(inode, filp, cmd, arg);
}