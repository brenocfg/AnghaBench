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
struct dentry {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  FILE__SETATTR ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 int cap_inode_removexattr (struct dentry*,char const*) ; 
 int /*<<< orphan*/  current_cred () ; 
 int dentry_has_perm (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_removexattr(struct dentry *dentry, const char *name)
{
	if (strcmp(name, XATTR_NAME_SELINUX)) {
		int rc = cap_inode_removexattr(dentry, name);
		if (rc)
			return rc;

		/* Not an attribute we recognize, so just check the
		   ordinary setattr permission. */
		return dentry_has_perm(current_cred(), dentry, FILE__SETATTR);
	}

	/* No one is allowed to remove a SELinux security label.
	   You can change the label, but all data must be labeled. */
	return -EACCES;
}