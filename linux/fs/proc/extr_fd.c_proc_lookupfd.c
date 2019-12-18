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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_fd_instantiate ; 
 struct dentry* proc_lookupfd_common (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_lookupfd(struct inode *dir, struct dentry *dentry,
				    unsigned int flags)
{
	return proc_lookupfd_common(dir, dentry, proc_fd_instantiate);
}