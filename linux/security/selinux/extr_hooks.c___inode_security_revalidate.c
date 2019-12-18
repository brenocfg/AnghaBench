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
struct inode_security_struct {scalar_t__ initialized; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ initialized; } ;

/* Variables and functions */
 int ECHILD ; 
 scalar_t__ LABEL_INITIALIZED ; 
 int /*<<< orphan*/  inode_doinit_with_dentry (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 TYPE_1__ selinux_state ; 

__attribute__((used)) static int __inode_security_revalidate(struct inode *inode,
				       struct dentry *dentry,
				       bool may_sleep)
{
	struct inode_security_struct *isec = selinux_inode(inode);

	might_sleep_if(may_sleep);

	if (selinux_state.initialized &&
	    isec->initialized != LABEL_INITIALIZED) {
		if (!may_sleep)
			return -ECHILD;

		/*
		 * Try reloading the inode security label.  This will fail if
		 * @opt_dentry is NULL and no dentry for this inode can be
		 * found; in that case, continue using the old label.
		 */
		inode_doinit_with_dentry(inode, dentry);
	}
	return 0;
}