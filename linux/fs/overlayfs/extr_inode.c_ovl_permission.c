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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int MAY_APPEND ; 
 int MAY_NOT_BLOCK ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int generic_permission (struct inode*,int) ; 
 int inode_permission (struct inode*,int) ; 
 struct inode* ovl_inode_lower (struct inode*) ; 
 struct inode* ovl_inode_upper (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int /*<<< orphan*/  special_file (int /*<<< orphan*/ ) ; 

int ovl_permission(struct inode *inode, int mask)
{
	struct inode *upperinode = ovl_inode_upper(inode);
	struct inode *realinode = upperinode ?: ovl_inode_lower(inode);
	const struct cred *old_cred;
	int err;

	/* Careful in RCU walk mode */
	if (!realinode) {
		WARN_ON(!(mask & MAY_NOT_BLOCK));
		return -ECHILD;
	}

	/*
	 * Check overlay inode with the creds of task and underlying inode
	 * with creds of mounter
	 */
	err = generic_permission(inode, mask);
	if (err)
		return err;

	old_cred = ovl_override_creds(inode->i_sb);
	if (!upperinode &&
	    !special_file(realinode->i_mode) && mask & MAY_WRITE) {
		mask &= ~(MAY_WRITE | MAY_APPEND);
		/* Make sure mounter can read file for copy up later */
		mask |= MAY_READ;
	}
	err = inode_permission(realinode, mask);
	revert_creds(old_cred);

	return err;
}