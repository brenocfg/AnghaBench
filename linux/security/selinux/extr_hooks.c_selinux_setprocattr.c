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
typedef  scalar_t__ u32 ;
struct task_security_struct {scalar_t__ sid; scalar_t__ sockcreate_sid; scalar_t__ keycreate_sid; scalar_t__ create_sid; scalar_t__ exec_sid; } ;
struct cred {int dummy; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SELINUX_ERR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY__CREATE ; 
 int /*<<< orphan*/  PROCESS__DYNTRANSITION ; 
 int /*<<< orphan*/  PROCESS__PTRACE ; 
 int /*<<< orphan*/  PROCESS__SETCURRENT ; 
 int /*<<< orphan*/  PROCESS__SETEXEC ; 
 int /*<<< orphan*/  PROCESS__SETFSCREATE ; 
 int /*<<< orphan*/  PROCESS__SETKEYCREATE ; 
 int /*<<< orphan*/  PROCESS__SETSOCKCREATE ; 
 int /*<<< orphan*/  SECCLASS_KEY ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  audit_log_n_untrustedstring (struct audit_buffer*,void*,size_t) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 int /*<<< orphan*/  current_is_single_threaded () ; 
 scalar_t__ current_sid () ; 
 int /*<<< orphan*/  has_cap_mac_admin (int) ; 
 struct cred* prepare_creds () ; 
 scalar_t__ ptrace_parent_sid () ; 
 int security_bounded_transition (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int security_context_to_sid (int /*<<< orphan*/ *,void*,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 int security_context_to_sid_force (int /*<<< orphan*/ *,void*,size_t,scalar_t__*) ; 
 struct task_security_struct* selinux_cred (struct cred*) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int selinux_setprocattr(const char *name, void *value, size_t size)
{
	struct task_security_struct *tsec;
	struct cred *new;
	u32 mysid = current_sid(), sid = 0, ptsid;
	int error;
	char *str = value;

	/*
	 * Basic control over ability to set these attributes at all.
	 */
	if (!strcmp(name, "exec"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETEXEC, NULL);
	else if (!strcmp(name, "fscreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETFSCREATE, NULL);
	else if (!strcmp(name, "keycreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETKEYCREATE, NULL);
	else if (!strcmp(name, "sockcreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETSOCKCREATE, NULL);
	else if (!strcmp(name, "current"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETCURRENT, NULL);
	else
		error = -EINVAL;
	if (error)
		return error;

	/* Obtain a SID for the context, if one was specified. */
	if (size && str[0] && str[0] != '\n') {
		if (str[size-1] == '\n') {
			str[size-1] = 0;
			size--;
		}
		error = security_context_to_sid(&selinux_state, value, size,
						&sid, GFP_KERNEL);
		if (error == -EINVAL && !strcmp(name, "fscreate")) {
			if (!has_cap_mac_admin(true)) {
				struct audit_buffer *ab;
				size_t audit_size;

				/* We strip a nul only if it is at the end, otherwise the
				 * context contains a nul and we should audit that */
				if (str[size - 1] == '\0')
					audit_size = size - 1;
				else
					audit_size = size;
				ab = audit_log_start(audit_context(),
						     GFP_ATOMIC,
						     AUDIT_SELINUX_ERR);
				audit_log_format(ab, "op=fscreate invalid_context=");
				audit_log_n_untrustedstring(ab, value, audit_size);
				audit_log_end(ab);

				return error;
			}
			error = security_context_to_sid_force(
						      &selinux_state,
						      value, size, &sid);
		}
		if (error)
			return error;
	}

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	/* Permission checking based on the specified context is
	   performed during the actual operation (execve,
	   open/mkdir/...), when we know the full context of the
	   operation.  See selinux_bprm_set_creds for the execve
	   checks and may_create for the file creation checks. The
	   operation will then fail if the context is not permitted. */
	tsec = selinux_cred(new);
	if (!strcmp(name, "exec")) {
		tsec->exec_sid = sid;
	} else if (!strcmp(name, "fscreate")) {
		tsec->create_sid = sid;
	} else if (!strcmp(name, "keycreate")) {
		if (sid) {
			error = avc_has_perm(&selinux_state, mysid, sid,
					     SECCLASS_KEY, KEY__CREATE, NULL);
			if (error)
				goto abort_change;
		}
		tsec->keycreate_sid = sid;
	} else if (!strcmp(name, "sockcreate")) {
		tsec->sockcreate_sid = sid;
	} else if (!strcmp(name, "current")) {
		error = -EINVAL;
		if (sid == 0)
			goto abort_change;

		/* Only allow single threaded processes to change context */
		error = -EPERM;
		if (!current_is_single_threaded()) {
			error = security_bounded_transition(&selinux_state,
							    tsec->sid, sid);
			if (error)
				goto abort_change;
		}

		/* Check permissions for the transition. */
		error = avc_has_perm(&selinux_state,
				     tsec->sid, sid, SECCLASS_PROCESS,
				     PROCESS__DYNTRANSITION, NULL);
		if (error)
			goto abort_change;

		/* Check for ptracing, and update the task SID if ok.
		   Otherwise, leave SID unchanged and fail. */
		ptsid = ptrace_parent_sid();
		if (ptsid != 0) {
			error = avc_has_perm(&selinux_state,
					     ptsid, sid, SECCLASS_PROCESS,
					     PROCESS__PTRACE, NULL);
			if (error)
				goto abort_change;
		}

		tsec->sid = sid;
	} else {
		error = -EINVAL;
		goto abort_change;
	}

	commit_creds(new);
	return size;

abort_change:
	abort_creds(new);
	return error;
}