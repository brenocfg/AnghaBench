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
struct superblock_security_struct {int flags; } ;
struct inode_security_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;
struct inode {int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int EACCES ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LABEL_INITIALIZED ; 
 int SBLABEL_MNT ; 
 int /*<<< orphan*/  XATTR_SELINUX_SUFFIX ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int /*<<< orphan*/ ) ; 
 struct inode_security_struct* inode_security_novalidate (struct inode*) ; 
 int security_context_to_sid (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_setsecurity(struct inode *inode, const char *name,
				     const void *value, size_t size, int flags)
{
	struct inode_security_struct *isec = inode_security_novalidate(inode);
	struct superblock_security_struct *sbsec = inode->i_sb->s_security;
	u32 newsid;
	int rc;

	if (strcmp(name, XATTR_SELINUX_SUFFIX))
		return -EOPNOTSUPP;

	if (!(sbsec->flags & SBLABEL_MNT))
		return -EOPNOTSUPP;

	if (!value || !size)
		return -EACCES;

	rc = security_context_to_sid(&selinux_state, value, size, &newsid,
				     GFP_KERNEL);
	if (rc)
		return rc;

	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = newsid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);
	return 0;
}