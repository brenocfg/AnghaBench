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
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct file_security_struct {scalar_t__ sid; } ;
struct file {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct file* file; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD__USE ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_FILE ; 
 int /*<<< orphan*/  SECCLASS_FD ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int bpf_fd_pass (struct file*,scalar_t__) ; 
 scalar_t__ cred_sid (struct cred const*) ; 
 struct inode* file_inode (struct file*) ; 
 int inode_has_perm (struct cred const*,struct inode*,scalar_t__,struct common_audit_data*) ; 
 struct file_security_struct* selinux_file (struct file*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int file_has_perm(const struct cred *cred,
			 struct file *file,
			 u32 av)
{
	struct file_security_struct *fsec = selinux_file(file);
	struct inode *inode = file_inode(file);
	struct common_audit_data ad;
	u32 sid = cred_sid(cred);
	int rc;

	ad.type = LSM_AUDIT_DATA_FILE;
	ad.u.file = file;

	if (sid != fsec->sid) {
		rc = avc_has_perm(&selinux_state,
				  sid, fsec->sid,
				  SECCLASS_FD,
				  FD__USE,
				  &ad);
		if (rc)
			goto out;
	}

#ifdef CONFIG_BPF_SYSCALL
	rc = bpf_fd_pass(file, cred_sid(cred));
	if (rc)
		return rc;
#endif

	/* av is zero if only checking access to the descriptor. */
	rc = 0;
	if (av)
		rc = inode_has_perm(cred, inode, av, &ad);

out:
	return rc;
}