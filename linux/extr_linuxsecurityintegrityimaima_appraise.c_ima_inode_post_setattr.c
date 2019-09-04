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
struct integrity_iint_cache {int /*<<< orphan*/  atomic_flags; } ;
struct inode {int i_opflags; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int IMA_APPRAISE ; 
 int /*<<< orphan*/  IMA_CHANGE_ATTR ; 
 int /*<<< orphan*/  IMA_UPDATE_XATTR ; 
 int IOP_XATTR ; 
 int /*<<< orphan*/  MAY_ACCESS ; 
 int /*<<< orphan*/  POST_SETATTR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XATTR_NAME_IMA ; 
 int /*<<< orphan*/  __vfs_removexattr (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int ima_must_appraise (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ima_policy_flag ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ima_inode_post_setattr(struct dentry *dentry)
{
	struct inode *inode = d_backing_inode(dentry);
	struct integrity_iint_cache *iint;
	int action;

	if (!(ima_policy_flag & IMA_APPRAISE) || !S_ISREG(inode->i_mode)
	    || !(inode->i_opflags & IOP_XATTR))
		return;

	action = ima_must_appraise(inode, MAY_ACCESS, POST_SETATTR);
	if (!action)
		__vfs_removexattr(dentry, XATTR_NAME_IMA);
	iint = integrity_iint_find(inode);
	if (iint) {
		set_bit(IMA_CHANGE_ATTR, &iint->atomic_flags);
		if (!action)
			clear_bit(IMA_UPDATE_XATTR, &iint->atomic_flags);
	}
}