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
typedef  int /*<<< orphan*/  u32 ;
struct inode_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
struct common_audit_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 struct inode_security_struct* selinux_inode (struct inode*) ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 

__attribute__((used)) static int inode_has_perm(const struct cred *cred,
			  struct inode *inode,
			  u32 perms,
			  struct common_audit_data *adp)
{
	struct inode_security_struct *isec;
	u32 sid;

	validate_creds(cred);

	if (unlikely(IS_PRIVATE(inode)))
		return 0;

	sid = cred_sid(cred);
	isec = selinux_inode(inode);

	return avc_has_perm(&selinux_state,
			    sid, isec->sid, isec->sclass, perms, adp);
}