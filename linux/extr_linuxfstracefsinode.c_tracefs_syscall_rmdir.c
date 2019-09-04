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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int (* rmdir ) (char*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 char* get_dname (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int stub1 (char*) ; 
 TYPE_1__ tracefs_ops ; 

__attribute__((used)) static int tracefs_syscall_rmdir(struct inode *inode, struct dentry *dentry)
{
	char *name;
	int ret;

	name = get_dname(dentry);
	if (!name)
		return -ENOMEM;

	/*
	 * The rmdir call can call the generic functions that create
	 * the files within the tracefs system. It is up to the individual
	 * rmdir routine to handle races.
	 * This time we need to unlock not only the parent (inode) but
	 * also the directory that is being deleted.
	 */
	inode_unlock(inode);
	inode_unlock(dentry->d_inode);

	ret = tracefs_ops.rmdir(name);

	inode_lock_nested(inode, I_MUTEX_PARENT);
	inode_lock(dentry->d_inode);

	kfree(name);

	return ret;
}