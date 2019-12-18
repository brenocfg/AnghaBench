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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* mkdir ) (char*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 char* get_dname (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int stub1 (char*) ; 
 TYPE_1__ tracefs_ops ; 

__attribute__((used)) static int tracefs_syscall_mkdir(struct inode *inode, struct dentry *dentry, umode_t mode)
{
	char *name;
	int ret;

	name = get_dname(dentry);
	if (!name)
		return -ENOMEM;

	/*
	 * The mkdir call can call the generic functions that create
	 * the files within the tracefs system. It is up to the individual
	 * mkdir routine to handle races.
	 */
	inode_unlock(inode);
	ret = tracefs_ops.mkdir(name);
	inode_lock(inode);

	kfree(name);

	return ret;
}