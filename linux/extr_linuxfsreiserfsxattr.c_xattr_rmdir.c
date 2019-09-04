#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_5__ {int (* rmdir ) (struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 TYPE_2__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 int stub1 (struct inode*,struct dentry*) ; 

__attribute__((used)) static int xattr_rmdir(struct inode *dir, struct dentry *dentry)
{
	int error;

	BUG_ON(!inode_is_locked(dir));

	inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
	error = dir->i_op->rmdir(dir, dentry);
	if (!error)
		d_inode(dentry)->i_flags |= S_DEAD;
	inode_unlock(d_inode(dentry));
	if (!error)
		d_delete(dentry);

	return error;
}