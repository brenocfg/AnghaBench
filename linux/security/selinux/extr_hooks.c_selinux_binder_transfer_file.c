#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct task_struct {int dummy; } ;
struct inode_security_struct {scalar_t__ sid; int /*<<< orphan*/  sclass; } ;
struct file_security_struct {scalar_t__ sid; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {TYPE_2__ path; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD__USE ; 
 int /*<<< orphan*/  IS_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_PATH ; 
 int /*<<< orphan*/  SECCLASS_FD ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 struct inode_security_struct* backing_inode_security (struct dentry*) ; 
 int bpf_fd_pass (struct file*,scalar_t__) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  file_to_av (struct file*) ; 
 struct file_security_struct* selinux_file (struct file*) ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ task_sid (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_binder_transfer_file(struct task_struct *from,
					struct task_struct *to,
					struct file *file)
{
	u32 sid = task_sid(to);
	struct file_security_struct *fsec = selinux_file(file);
	struct dentry *dentry = file->f_path.dentry;
	struct inode_security_struct *isec;
	struct common_audit_data ad;
	int rc;

	ad.type = LSM_AUDIT_DATA_PATH;
	ad.u.path = file->f_path;

	if (sid != fsec->sid) {
		rc = avc_has_perm(&selinux_state,
				  sid, fsec->sid,
				  SECCLASS_FD,
				  FD__USE,
				  &ad);
		if (rc)
			return rc;
	}

#ifdef CONFIG_BPF_SYSCALL
	rc = bpf_fd_pass(file, sid);
	if (rc)
		return rc;
#endif

	if (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		return 0;

	isec = backing_inode_security(dentry);
	return avc_has_perm(&selinux_state,
			    sid, isec->sid, isec->sclass, file_to_av(file),
			    &ad);
}