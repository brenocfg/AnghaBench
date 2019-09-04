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
typedef  int u32 ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_SELINUX_SUFFIX ; 
 scalar_t__ has_cap_mac_admin (int) ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int security_sid_to_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int*) ; 
 int security_sid_to_context_force (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_getsecurity(struct inode *inode, const char *name, void **buffer, bool alloc)
{
	u32 size;
	int error;
	char *context = NULL;
	struct inode_security_struct *isec;

	if (strcmp(name, XATTR_SELINUX_SUFFIX))
		return -EOPNOTSUPP;

	/*
	 * If the caller has CAP_MAC_ADMIN, then get the raw context
	 * value even if it is not defined by current policy; otherwise,
	 * use the in-core value under current policy.
	 * Use the non-auditing forms of the permission checks since
	 * getxattr may be called by unprivileged processes commonly
	 * and lack of permission just means that we fall back to the
	 * in-core context value, not a denial.
	 */
	isec = inode_security(inode);
	if (has_cap_mac_admin(false))
		error = security_sid_to_context_force(&selinux_state,
						      isec->sid, &context,
						      &size);
	else
		error = security_sid_to_context(&selinux_state, isec->sid,
						&context, &size);
	if (error)
		return error;
	error = size;
	if (alloc) {
		*buffer = context;
		goto out_nofree;
	}
	kfree(context);
out_nofree:
	return error;
}