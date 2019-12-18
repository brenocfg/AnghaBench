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
struct user_namespace {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct user_namespace* s_user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETFCAP ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  XATTR_NAME_CAPS ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX_LEN ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cap_inode_removexattr(struct dentry *dentry, const char *name)
{
	struct user_namespace *user_ns = dentry->d_sb->s_user_ns;

	/* Ignore non-security xattrs */
	if (strncmp(name, XATTR_SECURITY_PREFIX,
			XATTR_SECURITY_PREFIX_LEN) != 0)
		return 0;

	if (strcmp(name, XATTR_NAME_CAPS) == 0) {
		/* security.capability gets namespaced */
		struct inode *inode = d_backing_inode(dentry);
		if (!inode)
			return -EINVAL;
		if (!capable_wrt_inode_uidgid(inode, CAP_SETFCAP))
			return -EPERM;
		return 0;
	}

	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return -EPERM;
	return 0;
}