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
struct proc_ns_operations {int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {struct proc_ns_operations* d_fsdata; } ;

/* Variables and functions */
 struct inode* d_inode (struct dentry*) ; 
 char* dynamic_dname (struct dentry*,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ns_dname(struct dentry *dentry, char *buffer, int buflen)
{
	struct inode *inode = d_inode(dentry);
	const struct proc_ns_operations *ns_ops = dentry->d_fsdata;

	return dynamic_dname(dentry, buffer, buflen, "%s:[%lu]",
		ns_ops->name, inode->i_ino);
}