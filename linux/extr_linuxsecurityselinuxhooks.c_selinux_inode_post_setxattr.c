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
typedef  int /*<<< orphan*/  u32 ;
struct inode_security_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_INITIALIZED ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 struct inode_security_struct* backing_inode_security (struct dentry*) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int security_context_to_sid_force (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selinux_inode_post_setxattr(struct dentry *dentry, const char *name,
					const void *value, size_t size,
					int flags)
{
	struct inode *inode = d_backing_inode(dentry);
	struct inode_security_struct *isec;
	u32 newsid;
	int rc;

	if (strcmp(name, XATTR_NAME_SELINUX)) {
		/* Not an attribute we recognize, so nothing to do. */
		return;
	}

	rc = security_context_to_sid_force(&selinux_state, value, size,
					   &newsid);
	if (rc) {
		pr_err("SELinux:  unable to map context to SID"
		       "for (%s, %lu), rc=%d\n",
		       inode->i_sb->s_id, inode->i_ino, -rc);
		return;
	}

	isec = backing_inode_security(dentry);
	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = newsid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);

	return;
}