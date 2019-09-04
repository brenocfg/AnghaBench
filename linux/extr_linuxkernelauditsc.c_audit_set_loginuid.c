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
struct task_struct {unsigned int sessionid; int /*<<< orphan*/  loginuid; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 unsigned int AUDIT_SID_UNSET ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_get_loginuid (struct task_struct*) ; 
 unsigned int audit_get_sessionid (struct task_struct*) ; 
 int /*<<< orphan*/  audit_log_set_loginuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int audit_set_loginuid_perm (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  session_id ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int audit_set_loginuid(kuid_t loginuid)
{
	struct task_struct *task = current;
	unsigned int oldsessionid, sessionid = AUDIT_SID_UNSET;
	kuid_t oldloginuid;
	int rc;

	oldloginuid = audit_get_loginuid(current);
	oldsessionid = audit_get_sessionid(current);

	rc = audit_set_loginuid_perm(loginuid);
	if (rc)
		goto out;

	/* are we setting or clearing? */
	if (uid_valid(loginuid)) {
		sessionid = (unsigned int)atomic_inc_return(&session_id);
		if (unlikely(sessionid == AUDIT_SID_UNSET))
			sessionid = (unsigned int)atomic_inc_return(&session_id);
	}

	task->sessionid = sessionid;
	task->loginuid = loginuid;
out:
	audit_log_set_loginuid(oldloginuid, loginuid, oldsessionid, sessionid, rc);
	return rc;
}