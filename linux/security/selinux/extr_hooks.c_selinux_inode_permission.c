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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct cred {int dummy; } ;
struct av_decision {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_NONBLOCKING ; 
 int /*<<< orphan*/  FILE__AUDIT_ACCESS ; 
 scalar_t__ IS_ERR (struct inode_security_struct*) ; 
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int MAY_ACCESS ; 
 int MAY_APPEND ; 
 int MAY_EXEC ; 
 int MAY_NOT_BLOCK ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int PTR_ERR (struct inode_security_struct*) ; 
 int audit_inode_permission (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  avc_audit_required (int /*<<< orphan*/ ,struct av_decision*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int avc_has_perm_noaudit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct av_decision*) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  file_mask_to_av (int /*<<< orphan*/ ,int) ; 
 struct inode_security_struct* inode_security_rcu (struct inode*,unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 

__attribute__((used)) static int selinux_inode_permission(struct inode *inode, int mask)
{
	const struct cred *cred = current_cred();
	u32 perms;
	bool from_access;
	unsigned flags = mask & MAY_NOT_BLOCK;
	struct inode_security_struct *isec;
	u32 sid;
	struct av_decision avd;
	int rc, rc2;
	u32 audited, denied;

	from_access = mask & MAY_ACCESS;
	mask &= (MAY_READ|MAY_WRITE|MAY_EXEC|MAY_APPEND);

	/* No permission to check.  Existence test. */
	if (!mask)
		return 0;

	validate_creds(cred);

	if (unlikely(IS_PRIVATE(inode)))
		return 0;

	perms = file_mask_to_av(inode->i_mode, mask);

	sid = cred_sid(cred);
	isec = inode_security_rcu(inode, flags & MAY_NOT_BLOCK);
	if (IS_ERR(isec))
		return PTR_ERR(isec);

	rc = avc_has_perm_noaudit(&selinux_state,
				  sid, isec->sid, isec->sclass, perms,
				  (flags & MAY_NOT_BLOCK) ? AVC_NONBLOCKING : 0,
				  &avd);
	audited = avc_audit_required(perms, &avd, rc,
				     from_access ? FILE__AUDIT_ACCESS : 0,
				     &denied);
	if (likely(!audited))
		return rc;

	rc2 = audit_inode_permission(inode, perms, audited, denied, rc, flags);
	if (rc2)
		return rc2;
	return rc;
}