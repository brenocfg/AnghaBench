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
struct file {int f_flags; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  cifs_fscache_disable_inode_cookie (struct inode*) ; 
 int /*<<< orphan*/  cifs_fscache_enable_inode_cookie (struct inode*) ; 

void cifs_fscache_set_inode_cookie(struct inode *inode, struct file *filp)
{
	if ((filp->f_flags & O_ACCMODE) != O_RDONLY)
		cifs_fscache_disable_inode_cookie(inode);
	else
		cifs_fscache_enable_inode_cookie(inode);
}