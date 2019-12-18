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
struct iattr {unsigned int ia_valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;

/* Variables and functions */
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  AUDIT_INTEGRITY_METADATA ; 
 int EPERM ; 
 int EVM_ALLOW_METADATA_WRITES ; 
 int INTEGRITY_NOXATTRS ; 
 int INTEGRITY_PASS ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int evm_initialized ; 
 int evm_verify_current_integrity (struct dentry*) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * integrity_status_msg ; 

int evm_inode_setattr(struct dentry *dentry, struct iattr *attr)
{
	unsigned int ia_valid = attr->ia_valid;
	enum integrity_status evm_status;

	/* Policy permits modification of the protected attrs even though
	 * there's no HMAC key loaded
	 */
	if (evm_initialized & EVM_ALLOW_METADATA_WRITES)
		return 0;

	if (!(ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID)))
		return 0;
	evm_status = evm_verify_current_integrity(dentry);
	if ((evm_status == INTEGRITY_PASS) ||
	    (evm_status == INTEGRITY_NOXATTRS))
		return 0;
	integrity_audit_msg(AUDIT_INTEGRITY_METADATA, d_backing_inode(dentry),
			    dentry->d_name.name, "appraise_metadata",
			    integrity_status_msg[evm_status], -EPERM, 0);
	return -EPERM;
}