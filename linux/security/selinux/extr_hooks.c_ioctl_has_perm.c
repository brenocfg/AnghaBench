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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct lsm_ioctlop_audit {int cmd; int /*<<< orphan*/  path; } ;
struct inode_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct inode {int dummy; } ;
struct file_security_struct {scalar_t__ sid; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct lsm_ioctlop_audit* op; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD__USE ; 
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_IOCTL_OP ; 
 int /*<<< orphan*/  SECCLASS_FD ; 
 int avc_has_extended_perms (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,struct common_audit_data*) ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 scalar_t__ cred_sid (struct cred const*) ; 
 struct inode* file_inode (struct file*) ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 struct file_security_struct* selinux_file (struct file*) ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_has_perm(const struct cred *cred, struct file *file,
		u32 requested, u16 cmd)
{
	struct common_audit_data ad;
	struct file_security_struct *fsec = selinux_file(file);
	struct inode *inode = file_inode(file);
	struct inode_security_struct *isec;
	struct lsm_ioctlop_audit ioctl;
	u32 ssid = cred_sid(cred);
	int rc;
	u8 driver = cmd >> 8;
	u8 xperm = cmd & 0xff;

	ad.type = LSM_AUDIT_DATA_IOCTL_OP;
	ad.u.op = &ioctl;
	ad.u.op->cmd = cmd;
	ad.u.op->path = file->f_path;

	if (ssid != fsec->sid) {
		rc = avc_has_perm(&selinux_state,
				  ssid, fsec->sid,
				SECCLASS_FD,
				FD__USE,
				&ad);
		if (rc)
			goto out;
	}

	if (unlikely(IS_PRIVATE(inode)))
		return 0;

	isec = inode_security(inode);
	rc = avc_has_extended_perms(&selinux_state,
				    ssid, isec->sid, isec->sclass,
				    requested, driver, xperm, &ad);
out:
	return rc;
}