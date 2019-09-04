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
struct dentry {int /*<<< orphan*/  d_inode; struct dentry* d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int __tracefs_remove (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracefs_mount ; 
 int /*<<< orphan*/  tracefs_mount_count ; 

void tracefs_remove(struct dentry *dentry)
{
	struct dentry *parent;
	int ret;

	if (IS_ERR_OR_NULL(dentry))
		return;

	parent = dentry->d_parent;
	inode_lock(parent->d_inode);
	ret = __tracefs_remove(dentry, parent);
	inode_unlock(parent->d_inode);
	if (!ret)
		simple_release_fs(&tracefs_mount, &tracefs_mount_count);
}