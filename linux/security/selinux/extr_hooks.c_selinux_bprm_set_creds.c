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
struct task_security_struct {scalar_t__ sid; scalar_t__ osid; scalar_t__ exec_sid; scalar_t__ sockcreate_sid; scalar_t__ keycreate_sid; scalar_t__ create_sid; } ;
struct linux_binprm {int unsafe; int secureexec; int /*<<< orphan*/  per_clear; int /*<<< orphan*/  file; int /*<<< orphan*/  cred; scalar_t__ called_set_creds; } ;
struct inode_security_struct {scalar_t__ sid; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FILE__ENTRYPOINT ; 
 int /*<<< orphan*/  FILE__EXECUTE_NO_TRANS ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_FILE ; 
 int LSM_UNSAFE_PTRACE ; 
 int LSM_UNSAFE_SHARE ; 
 int /*<<< orphan*/  PER_CLEAR_ON_SETID ; 
 int /*<<< orphan*/  PROCESS__NOATSECURE ; 
 int /*<<< orphan*/  PROCESS__PTRACE ; 
 int /*<<< orphan*/  PROCESS__SHARE ; 
 int /*<<< orphan*/  PROCESS__TRANSITION ; 
 int /*<<< orphan*/  SECCLASS_FILE ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int check_nnp_nosuid (struct linux_binprm*,struct task_security_struct const*,struct task_security_struct*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 scalar_t__ ptrace_parent_sid () ; 
 int security_transition_sid (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 void* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_bprm_set_creds(struct linux_binprm *bprm)
{
	const struct task_security_struct *old_tsec;
	struct task_security_struct *new_tsec;
	struct inode_security_struct *isec;
	struct common_audit_data ad;
	struct inode *inode = file_inode(bprm->file);
	int rc;

	/* SELinux context only depends on initial program or script and not
	 * the script interpreter */
	if (bprm->called_set_creds)
		return 0;

	old_tsec = selinux_cred(current_cred());
	new_tsec = selinux_cred(bprm->cred);
	isec = inode_security(inode);

	/* Default to the current task SID. */
	new_tsec->sid = old_tsec->sid;
	new_tsec->osid = old_tsec->sid;

	/* Reset fs, key, and sock SIDs on execve. */
	new_tsec->create_sid = 0;
	new_tsec->keycreate_sid = 0;
	new_tsec->sockcreate_sid = 0;

	if (old_tsec->exec_sid) {
		new_tsec->sid = old_tsec->exec_sid;
		/* Reset exec SID on execve. */
		new_tsec->exec_sid = 0;

		/* Fail on NNP or nosuid if not an allowed transition. */
		rc = check_nnp_nosuid(bprm, old_tsec, new_tsec);
		if (rc)
			return rc;
	} else {
		/* Check for a default transition on this program. */
		rc = security_transition_sid(&selinux_state, old_tsec->sid,
					     isec->sid, SECCLASS_PROCESS, NULL,
					     &new_tsec->sid);
		if (rc)
			return rc;

		/*
		 * Fallback to old SID on NNP or nosuid if not an allowed
		 * transition.
		 */
		rc = check_nnp_nosuid(bprm, old_tsec, new_tsec);
		if (rc)
			new_tsec->sid = old_tsec->sid;
	}

	ad.type = LSM_AUDIT_DATA_FILE;
	ad.u.file = bprm->file;

	if (new_tsec->sid == old_tsec->sid) {
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, isec->sid,
				  SECCLASS_FILE, FILE__EXECUTE_NO_TRANS, &ad);
		if (rc)
			return rc;
	} else {
		/* Check permissions for the transition. */
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, new_tsec->sid,
				  SECCLASS_PROCESS, PROCESS__TRANSITION, &ad);
		if (rc)
			return rc;

		rc = avc_has_perm(&selinux_state,
				  new_tsec->sid, isec->sid,
				  SECCLASS_FILE, FILE__ENTRYPOINT, &ad);
		if (rc)
			return rc;

		/* Check for shared state */
		if (bprm->unsafe & LSM_UNSAFE_SHARE) {
			rc = avc_has_perm(&selinux_state,
					  old_tsec->sid, new_tsec->sid,
					  SECCLASS_PROCESS, PROCESS__SHARE,
					  NULL);
			if (rc)
				return -EPERM;
		}

		/* Make sure that anyone attempting to ptrace over a task that
		 * changes its SID has the appropriate permit */
		if (bprm->unsafe & LSM_UNSAFE_PTRACE) {
			u32 ptsid = ptrace_parent_sid();
			if (ptsid != 0) {
				rc = avc_has_perm(&selinux_state,
						  ptsid, new_tsec->sid,
						  SECCLASS_PROCESS,
						  PROCESS__PTRACE, NULL);
				if (rc)
					return -EPERM;
			}
		}

		/* Clear any possibly unsafe personality bits on exec: */
		bprm->per_clear |= PER_CLEAR_ON_SETID;

		/* Enable secure mode for SIDs transitions unless
		   the noatsecure permission is granted between
		   the two SIDs, i.e. ahp returns 0. */
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, new_tsec->sid,
				  SECCLASS_PROCESS, PROCESS__NOATSECURE,
				  NULL);
		bprm->secureexec |= !!rc;
	}

	return 0;
}