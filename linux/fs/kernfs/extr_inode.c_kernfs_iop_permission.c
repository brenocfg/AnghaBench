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
struct kernfs_node {int dummy; } ;
struct inode {struct kernfs_node* i_private; } ;

/* Variables and functions */
 int ECHILD ; 
 int MAY_NOT_BLOCK ; 
 int generic_permission (struct inode*,int) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  kernfs_refresh_inode (struct kernfs_node*,struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kernfs_iop_permission(struct inode *inode, int mask)
{
	struct kernfs_node *kn;

	if (mask & MAY_NOT_BLOCK)
		return -ECHILD;

	kn = inode->i_private;

	mutex_lock(&kernfs_mutex);
	kernfs_refresh_inode(kn, inode);
	mutex_unlock(&kernfs_mutex);

	return generic_permission(inode, mask);
}